//
// Created by dza02 on 6/30/2021.
//

#ifndef WORKSHOP_KV_PAIR_H
#define WORKSHOP_KV_PAIR_H

#include <string.h>
#include <stdlib.h>

typedef unsigned long value_t;

typedef struct kv_pair{
    char* key;
    value_t value;
} kv_pair_s;

/*
 * initializes a kv_pair
 * kvp must be a valid pointer
 * key can be NULL
 * key is copied
*/
extern kv_pair_s* kvp_init(kv_pair_s* kvp, const char* key, value_t value);

/*
 * creates and initializes a new kvp_pair
 * key shouldn't be NULL
 */
extern kv_pair_s kvp_create(const char* key, value_t value);

/*
 * destroys a kv_pair that was created with kvp_create
 * (or initialized with kvp_init)
 * kvp cannot be NULL
 */
extern void kvp_destroy(kv_pair_s* kvp);

#endif //WORKSHOP_KV_PAIR_H
