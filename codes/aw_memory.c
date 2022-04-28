//
// Created by pengc on 2022/4/28.
//

#include <aw_memory.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////
////

void* aw_memory_alloc(aw_size_t size, const char* file, int line){
    void* ptr;
    assert(size>0);
    ptr = malloc(size);
    assert(ptr);
    return ptr;
}

void* aw_memory_calloc(aw_size_t numberOfElement, aw_size_t elementSize, const char* file, int line){
    void *ptr;
    assert(numberOfElement>0);
    assert(elementSize>0);
    ptr = calloc(numberOfElement, elementSize);
    assert(ptr);
    return ptr;
}

void* aw_memory_resize(void* ptr, aw_size_t size, const char* file, int line){
    assert(ptr);
    assert(size>0);
    ptr = realloc(ptr, size);
    assert(ptr);
    return ptr;
}

void aw_memory_free(void* ptr, const char* file, int line){
    if(ptr) free(ptr);
}