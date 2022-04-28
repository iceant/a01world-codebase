//
// Created by pengc on 2022/4/28.
//

#ifndef INCLUDED_AW_VECTOR_H
#define INCLUDED_AW_VECTOR_H

#ifndef INCLUDED_AW_TYPES_H
#include <aw_types.h>
#endif // INCLUDED_AW_TYPES_H

#ifndef INCLUDED_STDIO_H
#define INCLUDED_STDIO_H
#include <stdio.h>
#endif // INCLUDED_STDIO_H

////////////////////////////////////////////////////////////////////////////////
////
typedef struct aw_vector_t aw_vector_t;

////////////////////////////////////////////////////////////////////////////////
////
aw_vector_t *aw_vector_new(aw_size_t capacity);

void aw_vector_free(aw_vector_t** pVector);

void aw_vector_set(aw_vector_t* vector, aw_size_t idx, void* value);

void* aw_vector_get(aw_vector_t* vector, aw_size_t idx);

void aw_vector_fetch(aw_vector_t* vector, aw_size_t idx, void** result);

void aw_vector_append(aw_vector_t* vector, void* value);

aw_size_t aw_vector_size(aw_vector_t *vector);
    // element numbers in vector

aw_size_t aw_vector_capacity(aw_vector_t *vector);

void* aw_vector_pop_back(aw_vector_t* vector);

void aw_vector_fetch_back(aw_vector_t* vector, void** result);

void aw_vector_hexdump(aw_vector_t *vector, FILE *stream);

#endif //INCLUDED_AW_VECTOR_H
