//
// Created by pengc on 2022/4/28.
//

#include <aw_vector.h>
#include <aw_memory.h>
#include <assert.h>
#include <aw_hexdump.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
////
struct aw_vector_t{
    aw_size_t capacity;
    aw_size_t size;
    void** d_data_p;
};

#define AW_VECTOR_GROWTH_FACTOR 2
////////////////////////////////////////////////////////////////////////////////
////

aw_vector_t *aw_vector_new(aw_size_t capacity){
    aw_vector_t *p;

    assert(capacity>0);

    AW_NEW(p);
    assert(p);
    p->capacity = capacity;
    p->size = 0;
    p->d_data_p = AW_ALLOC(sizeof (*p->d_data_p) * capacity);
    assert(p->d_data_p);
    return p;
}

void aw_vector_free(aw_vector_t** pVector){
    assert(pVector && *pVector);
    AW_FREE((*pVector)->d_data_p);
    AW_FREE(*pVector);
}

void aw_vector_set(aw_vector_t* vector, aw_size_t idx, void* value){
    assert(vector);
    assert(idx>=0 && idx < vector->capacity);
    vector->d_data_p[idx] = value;
}

void* aw_vector_get(aw_vector_t* vector, aw_size_t idx){
    assert(vector);
    assert(idx>=0 && idx< vector->capacity);
    return vector->d_data_p[idx];
}

void aw_vector_fetch(aw_vector_t* vector, aw_size_t idx, void** result){
    assert(vector);
    assert(idx>=0 && idx< vector->capacity);
    assert(result);
    *result = vector->d_data_p[idx];
}

void aw_vector_append(aw_vector_t* vector, void* value){
    assert(vector);
    if(vector->size >= vector->capacity){
        aw_size_t newCapacity = AW_VECTOR_GROWTH_FACTOR * vector->capacity;
        assert(newCapacity <= AW_SIZE_MAX);
        void* newArray = AW_ALLOC(newCapacity * sizeof(*(vector->d_data_p)));
        assert(newArray);
        memcpy(newArray, vector->d_data_p, vector->size * sizeof (*(vector->d_data_p)));
        AW_FREE(vector->d_data_p);
        vector->d_data_p = newArray;
        vector->capacity = newCapacity;
    }
    vector->d_data_p[vector->size] = value;
    vector->size++;
}

aw_size_t aw_vector_size(aw_vector_t *vector){
    assert(vector);
    return vector->size;
}

aw_size_t aw_vector_capacity(aw_vector_t *vector){
    assert(vector);
    return vector->capacity;
}

void* aw_vector_pop_back(aw_vector_t* vector){
    assert(vector);
    if(vector->size>0) {
        return vector->d_data_p[--vector->size];
    }else {
        return NULL;
    }
}

void aw_vector_fetch_back(aw_vector_t* vector, void** result){
    assert(vector);
    assert(result);

    if(vector->size>0) {
        *result = vector->d_data_p[--vector->size];
    }else {
        *result = NULL;
    }
}

void aw_vector_hexdump(aw_vector_t *vector, FILE* stream){
    aw_hexdump(stream, vector->d_data_p, vector->capacity * sizeof(*vector->d_data_p));
}