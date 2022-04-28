//
// Created by pengc on 2022/4/29.
//

#ifndef INCLUDED_AW_HASHTABLE_H
#define INCLUDED_AW_HASHTABLE_H

#ifndef INCLUDED_AW_TYPES_H
#include <aw_types.h>
#endif // INCLUDED_AW_TYPES_H
////////////////////////////////////////////////////////////////////////////////
////

typedef struct aw_hashtable_t aw_hashtable_t;

typedef struct aw_hashtable_key_ops{
    aw_uint32_t (*hash)(const void* data, void* arg);
    void* (*cp)(const void* data, void* arg);
    void (*free)(void* data, void* arg);
    aw_bool_t (*eq)(const void* data1, const void *data2, void *arg);
    void* arg;
}aw_hashtable_key_ops;

typedef struct aw_hashtable_val_ops{
    void* (*cp)(const void *data, void *arg);
    void (*free)(void *data, void *arg);
    bool (*eq)(const void *data1, const void *data2, void *arg);
    void *arg;
}aw_hashtable_val_ops;

////////////////////////////////////////////////////////////////////////////////
////

aw_hashtable_t * aw_hashtable_new(aw_hashtable_key_ops keyOps, aw_hashtable_val_ops valOps);

void aw_hashtable_free(aw_hashtable_t ** pHashtable);

void* aw_hashtable_get(aw_hashtable_t* htable, const void* key);

aw_bool_t aw_hashtable_contains(aw_hashtable_t *htable, const void* key);

void aw_hashtable_put(aw_hashtable_t* htable, const void* key, const void* val);

aw_size_t aw_hashtable_numberOfCollisions(aw_hashtable_t* htable);

void aw_hashtable_foreach(aw_hashtable_t* htable, void (*apply)(const void* key, void* value, void* args), void* args);

#endif //INCLUDED_AW_HASHTABLE_H
