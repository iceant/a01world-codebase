//
// Created by pengc on 2022/4/29.
//

#include <aw_hashtable.h>
#include <aw_vector.h>
#include <aw_memory.h>
#include <assert.h>
////////////////////////////////////////////////////////////////////////////////
////

struct aw_hashtable_t {
    aw_size_t capacity;
    aw_size_t size;
    aw_vector_t **d_buckets_p;
    aw_hashtable_key_ops key_ops;
    aw_hashtable_val_ops val_ops;
};

typedef struct aw_hashtable_node_t{
    aw_uint32_t hash;
    void *key;
    void *value;
}aw_hashtable_node_t;

#define AW_HASHTABLE_CAPACITY_INIT 1024
#define AW_HASHTABLE_CAPACITY_GROWTH_FACTOR 2
#define AW_HASHTABLE_BUCKET_INIT_CAPACITY 8

////////////////////////////////////////////////////////////////////////////////
////

static aw_hashtable_node_t * aw_hashtable_get_node(aw_hashtable_t *htable, const void *key) {

    aw_hashtable_node_t *result = NULL;
    aw_hashtable_node_t *crt_node = NULL;
    aw_vector_t *crt_bucket = NULL;

    uint32_t computed_hash;
    size_t bucket_idx;

    computed_hash = htable->key_ops.hash(key, htable->key_ops.arg);
    bucket_idx = computed_hash % htable->capacity;
    crt_bucket = htable->d_buckets_p[bucket_idx];

    if (NULL!=crt_bucket) {
        for(aw_size_t i = 0; i < aw_vector_size(crt_bucket); ++i) {
            crt_node = aw_vector_get(crt_bucket, i);
            if (crt_node->hash == computed_hash) {
                if (htable->key_ops.eq(crt_node->key, key, htable->key_ops.arg)) {
                    result = crt_node;
                    break;
                }
            }
        }
    }
    return result;
}

static void aw_hashtable_grow(aw_hashtable_t *htable) {

    aw_vector_t **new_buckets;
    aw_vector_t *crt_bucket;
    aw_hashtable_node_t *crt_element;
    size_t new_capacity;
    size_t new_idx;

    new_capacity = htable->capacity * AW_HASHTABLE_CAPACITY_GROWTH_FACTOR;
    assert(new_capacity < AW_SIZE_MAX);

    new_buckets = AW_ALLOC(sizeof(*new_buckets) * new_capacity);
    assert(new_buckets);

    for(int i = 0; i < new_capacity; ++i) {
        new_buckets[i] = NULL;
    }

    // Rehash
    // For each (old) bucket
    for(int i = 0; i < htable->capacity; i++) {
        crt_bucket = htable->d_buckets_p[i];
        // For each element from the old bucket
        if (NULL!=crt_bucket) {
            for(int j = 0; j < aw_vector_size(crt_bucket); j++) {
                // For each element from the
                crt_element = aw_vector_get(crt_bucket, j);
                // Compute the new id for the new bucket
                new_idx = crt_element->hash % new_capacity;
                // If the bucket doesn't exist yet, we create yet
                if (NULL==new_buckets[new_idx]) {
                    new_buckets[new_idx] = aw_vector_new(AW_HASHTABLE_BUCKET_INIT_CAPACITY);
                }
                // Add the element to the corresponding bucket
                aw_vector_append(new_buckets[new_idx], crt_element);
            }
        }
    }

    htable->capacity = new_capacity;

    // Free the old buckets
    AW_FREE(htable->d_buckets_p);

    // Update with the new buckets
    htable->d_buckets_p = new_buckets;
}
////////////////////////////////////////////////////////////////////////////////
////

aw_hashtable_t * aw_hashtable_new(aw_hashtable_key_ops keyOps, aw_hashtable_val_ops valOps){
    aw_hashtable_t * p;
    AW_NEW(p);
    assert(p);

    p->capacity = AW_HASHTABLE_CAPACITY_INIT;
    p->size = 0;
    p->key_ops = keyOps;
    p->val_ops = valOps;
    p->d_buckets_p = AW_ALLOC(p->capacity * sizeof(*(p->d_buckets_p)));
    for(aw_size_t i=0; i<p->capacity; i++){
        p->d_buckets_p[i] = NULL;
    }
    return p;
}

void aw_hashtable_free(aw_hashtable_t ** pHashtable){
    aw_vector_t * crt;
    aw_hashtable_node_t *p;

    assert(pHashtable && *pHashtable);
    aw_hashtable_t * htable = *pHashtable;

    for(aw_size_t i = 0; i<htable->capacity; i++){
        crt = htable->d_buckets_p[i];
        if(crt){
            for(aw_size_t j=0; j< aw_vector_size(crt); j++){
                p = aw_vector_get(crt, j);
                htable->key_ops.free(p->key, htable->key_ops.arg);
                htable->val_ops.free(p->value, htable->val_ops.arg);
                AW_FREE(p);
            }
            aw_vector_free(&crt);
        }
    }

    AW_FREE(htable->d_buckets_p);
    AW_FREE(*pHashtable);
}

void* aw_hashtable_get(aw_hashtable_t* htable, const void* key){
    assert(htable);
    assert(key);

    aw_hashtable_node_t *result = aw_hashtable_get_node(htable, key);
    if(NULL==result) return NULL;
    return result->value;
}

aw_bool_t aw_hashtable_contains(aw_hashtable_t *htable, const void* key){
    assert(htable);
    assert(key);
    return aw_hashtable_get_node(htable, key)?AW_TRUE:AW_FALSE;
}

void aw_hashtable_put(aw_hashtable_t* htable, const void* key, const void* val){

    aw_hashtable_node_t *crt;
    size_t bucket_idx;

    assert(htable);
    assert(key);

    crt = aw_hashtable_get_node(htable, key);

    if (NULL!=crt) {
        // Key already exists
        // We need to update the value
        htable->val_ops.free(crt->value, htable->val_ops.arg);
        crt->value = val ? htable->val_ops.cp(val, htable->val_ops.arg) : 0;
    }else {
        // Key doesn't exist
        // - We create a node
        // - We add a node to the correspoding bucket
        crt = AW_ALLOC(sizeof(*crt));
        assert(crt);

        crt->hash = htable->key_ops.hash(key, htable->key_ops.arg);
        crt->key = htable->key_ops.cp(key, htable->key_ops.arg);
        crt->value = htable->val_ops.cp(val, htable->val_ops.arg);

        bucket_idx = crt->hash % htable->capacity;
        if (NULL==htable->d_buckets_p[bucket_idx]) {
            htable->d_buckets_p[bucket_idx] = aw_vector_new(AW_HASHTABLE_BUCKET_INIT_CAPACITY);
        }
        aw_vector_append(htable->d_buckets_p[bucket_idx], crt);

        // Element has been added successfully
        htable->size++;

        // Grow if needed
        if (htable->size >= htable->capacity) {
            aw_hashtable_grow(htable);
        }
    }
}

aw_size_t aw_hashtable_numberOfCollisions(aw_hashtable_t* htable){
    aw_size_t result;
    assert(htable);

    result = 0;
    for(aw_size_t i=0; i<htable->capacity; i++){
        aw_size_t sz = htable->d_buckets_p[i]?aw_vector_size(htable->d_buckets_p[i]):0;
        result +=((sz==0)?0:(sz-1));
    }
    return result;
}

void aw_hashtable_foreach(aw_hashtable_t* htable, void (*apply)(const void* key, void* value, void* args), void* args){
    aw_vector_t * bucket;
    aw_hashtable_node_t *node;

    assert(htable);
    assert(apply);

    for(aw_size_t i=0; i<htable->capacity; i++){
        bucket = htable->d_buckets_p[i];
        if(bucket==NULL) continue;
        for(aw_size_t j = 0; j<aw_vector_size(bucket); j++){
            node = aw_vector_get(bucket, j);
            apply(node->key, node->value, args);
        }
    }
}
