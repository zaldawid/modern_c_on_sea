//
// Created by dza02 on 6/30/2021.
//

#ifndef WORKSHOP_WORD_COUNTER_H
#define WORKSHOP_WORD_COUNTER_H
#include "../include/kv_pair.h"

// A counter (map of string->unsigned long)
typedef struct word_counter {
    kv_pair_s* data;
    size_t size;		// number of items in this set
    size_t capacity;   // size of the `data` array
} word_counter_s;

// Used for searching for a key
typedef struct key_index{
    size_t index;      // index of the kv_pair_s with the key or insertion index to maintain sorted property
    _Bool found;    // key was found
} key_index_s;

/*
 * Initializes a counter with a capacity
 * counter shouldn't be NULL, capacity should be > 0
 */
extern word_counter_s* cnt_init(word_counter_s* counter, size_t capacity);

/*
 * creates a word_counter_s with default capacity
 */
extern word_counter_s cnt_create();

/*
 * destroys a counter and its content freeing the memory
 * counter shouldn't be NULL
 */
extern void cnt_destroy(word_counter_s* counter);

/*
 * returns the index of the key if found (or index of insertion if key not found)
 */
extern key_index_s index_of(word_counter_s* counter, const char* key);

/*
 * inserts a new key-value pair or updates and existing one
 * returns: 1 (true) if inserted, 0 (false) if updated
 */
extern int insert(word_counter_s* counter, const char* key, value_t value);

/*
 * gets the value associated with a key (or `defaultValue` if key doesn't exist)
 */
extern unsigned long get_or_default(word_counter_s* counter, const char* key, value_t defaultValue);

/*
 * checks if a counter contains a key
 */
extern int contains(word_counter_s* counter, const char* key);

/*
 * increments a value associated with a key (or inserts with a count of 1)
 */
extern unsigned long increment(word_counter_s* counter, const char* key);

/*
 * a bit faster implementation of increment
 */
extern unsigned long increment_fast(word_counter_s* counter, const char* key);

#endif //WORKSHOP_WORD_COUNTER_H
