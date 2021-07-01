//
// Created by dza02 on 6/30/2021.
//

#include "../include/kv_pair.h"

/*
 * TODO 1: Change the types of some parameters that cannot be NULL to use the array syntax with static size
 * TODO 2: Refactor kvp_init to use compound literals for initialization
 * TODO 3: Can you refactor kvp_create to just one line of code using a compound literal? (It's not beautiful but surely neat)
 */

/*
 * initializes a kv_pair
 * kvp must be a valid pointer
 * key can be NULL
 * key is copied
*/
extern kv_pair_s* kvp_init(kv_pair_s* kvp, const char* key, value_t value){
    if (kvp){
        size_t length = key == NULL? 0 : strlen(key) + 1;
        if (length){
            if ((kvp->key = (char*)malloc(strlen(key) + 1))){
                memcpy(kvp->key, key, length);
                kvp->value = value;
            }
            else{
                kvp->value = 0;
            }
        }
        else{
            // key is NULL
            kvp->key = NULL;
            kvp->value = 0;
        }
    }
    return kvp;
}

/*
 * creates and initializes a new kvp_pair
 * key shouldn't be NULL
 */
kv_pair_s kvp_create(const char* key, value_t value){
    kv_pair_s pair;
    kvp_init(&pair, key, value);
    return pair;
}

/*
 * destroys a kv_pair that was created with kvp_create
 * (or initialized with kvp_init)
 * kvp cannot be NULL
 */
void kvp_destroy(kv_pair_s* kvp){
    if (kvp) {
        free((char*) kvp->key);
        kvp_init(kvp, NULL, 0);
    }
}






