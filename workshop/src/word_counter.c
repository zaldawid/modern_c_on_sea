//
// Created by dza02 on 6/30/2021.
//

#include "../include/word_counter.h"
#include "../include/kv_pair.h"

/*
 * TODO 1: Change the types of some parameters that cannot be NULL to use the array syntax with static size
 * TODO 2: Using `int` instead of `_Bool` has no place in modern C. Include stdbool.h and refactor all functions/ types
 *         where the TRUE and FALSE defines appear to use the proper Boolean type and the standard `true`, `false`
 * TODO 3: `index_of` returns `key_index_s`. It now uses a traditional approach of declaring a variable of this type and
 *         filling its fields later. Can you spot an opportunity for compound literals?
 * TODO 4: Readability of `cnt_init` can be improved with compound literals and some other simple refactoring techniques.
 *         It can easily become less than 10 lines of code, closing braces included. Up for a challenge?
 * TODO 5: Function `cnt_create` can be rewritten as a one-liner with a compound literal.
 *
*/

#define GROWTH_FACTOR  (2) // for resizing counter's capacity
#define DEFAULT_CAPACITY (64)
#define TRUE (1)
#define FALSE (0)

/*
 * inserts a key-value pair at a specific location, shifting elements if needed
 * returns 1 (true) if succeed, 0 (false) if not
 */
static int _insert_at(word_counter_s* counter, size_t index,  const char* key, value_t value);

/*
 * makes space if needed by resizing the counter's storage
 * returns 1 (true) if succeed, 0 (false) if not
 */
static int _ensure_capacity(word_counter_s* counter, size_t minimumCapacity);

word_counter_s* cnt_init(word_counter_s* counter, size_t capacity){
    if (counter) {
        if (capacity) {
            counter->size = 0;
            counter->data = (kv_pair_s*)malloc(capacity * sizeof(kv_pair_s));
            if (counter->data){
                counter->capacity = capacity;
            }
            else{
                counter->capacity = 0;
            }
        } else {
            counter->data = NULL;
            counter->size = 0;
            counter->capacity = 0;
        }
    }
    return counter;
}

word_counter_s cnt_create(){
    word_counter_s counter;
    cnt_init(&counter, DEFAULT_CAPACITY);
    return counter;
}

void cnt_destroy(word_counter_s* counter){
    for (size_t i = 0; i < counter->size; ++i){
        kvp_destroy(&counter->data[i]);
    }
    free(counter->data);
    cnt_init(counter, 0);
}

// return the index of the key if found (or index of insertion)
key_index_s index_of(word_counter_s* counter, const char* key){
    // a simple binary search

    key_index_s ret;

    long lo = 0, hi = (long)counter->size - 1;
    while (lo <= hi){
        long mid = lo + (hi - lo) / 2;

        int cmp = strcmp(counter->data[mid].key, key);

        if (cmp < 0){
            lo = mid + 1;
        }
        else if (cmp > 0){
            hi = mid - 1;
        }
        else{
            ret.index = mid;
            ret.found = TRUE;
            return ret;
        }
    }
    // key not found - `lo` is the index of insertion that maintains the ordered property
    ret.index = lo;
    ret.found = FALSE;
    return ret;
}


int insert(word_counter_s* counter, const char* key, value_t value){
    key_index_s index = index_of(counter, key);
    if (index.found){
        // update the value if an item with this key already exists
        counter->data[index.index].value = value;
        return TRUE;
    }
    else {
        // an item with this key doesn't exists yet
        // insert a new kv_pair_s at given index
        return _insert_at(counter, index.index, key, value);
    }
}

unsigned long get_or_default(word_counter_s* counter, const char* key, value_t defaultValue){
    key_index_s index = index_of(counter, key);
    if (index.found){
        return counter->data[index.index].value;
    }
    return defaultValue;
}

int contains(word_counter_s* counter, const char* key){
    return index_of(counter, key).found;
}

// implementation using existing functions:
unsigned long increment(word_counter_s* counter, const char* key){
    value_t value = get_or_default(counter, key, 0);
    if (insert(counter, key, value + 1)) {
        return value + 1;
    }
    else{
        return 0;
    };
}

// a bit faster implementation that doesn't have to search through the data array two times
unsigned long increment_fast(word_counter_s* counter, const char* key){
    key_index_s index = index_of(counter, key);
    if (index.found){
        return ++(counter->data[index.index].value);
    }
    else{
        return _insert_at(counter, index.index, key, 1);
    }
}

// Internal function, called to resize a word_counter_s if needed
int _ensure_capacity(word_counter_s* counter, size_t minimumCapacity){
    if (counter->capacity >= minimumCapacity) return TRUE;

    size_t capacity = counter->capacity;
    if (capacity == 0){
        capacity = DEFAULT_CAPACITY;
    }
    while (minimumCapacity > capacity){
        capacity *= GROWTH_FACTOR;
    }

    if (capacity > counter->capacity){
        kv_pair_s* data = (kv_pair_s*)realloc(counter->data, sizeof(kv_pair_s) * capacity);
        if (!data) {
            return FALSE;
        }
        counter->data = data;
        counter->capacity = capacity;
    }
    return TRUE;
}

// Internal function for inserting a key-value at index
// Returns: the inserted value
static int _insert_at(word_counter_s* counter, size_t index,  const char* key, value_t value){
    if (_ensure_capacity(counter, counter->size + 1)) {
        kv_pair_s pair = kvp_create(key, value);
        if (pair.key) {

            // shift the elements for insertion
            // this has no effect if appending at the end (index.index == counter->size)
            size_t sizeToMove = sizeof(kv_pair_s) * (counter->size - index);
            memmove(&(counter->data[index + 1]), &(counter->data[index]), sizeToMove);

            counter->data[index] = pair;
            ++counter->size;

            return TRUE;
        }
    }
    return FALSE;
}


