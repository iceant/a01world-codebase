//
// Created by pengc on 2022/4/28.
//

#ifndef INCLUDED_AW_MEMORY_H
#define INCLUDED_AW_MEMORY_H

#ifndef INCLUDED_AW_TYPES_H
#include <aw_types.h>
#endif // INCLUDED_AW_TYPES_H

////////////////////////////////////////////////////////////////////////////////
////
void* aw_memory_alloc(aw_size_t size, const char* file, int line);

void* aw_memory_calloc(aw_size_t numberOfElement, aw_size_t elementSize, const char* file, int line);

void* aw_memory_resize(void* ptr, aw_size_t size, const char* file, int line);

void aw_memory_free(void* ptr, const char* file, int line);

////////////////////////////////////////////////////////////////////////////////
////
#define AW_ALLOC(nbytes) aw_memory_alloc((nbytes), __FILE__, __LINE__)
#define AW_CALLOC(n, nbytes) aw_memory_calloc((n), (nbytes), __FILE__, __LINE__)
#define AW_RESIZE(ptr, nbytes) ((ptr)=aw_memory_resize((ptr), (nbytes), __FILE__, __LINE__))
#define AW_FREE(ptr) ((void)(aw_memory_free((ptr), __FILE__, __LINE__), (ptr)=0))

#define AW_NEW(p) ((p)=AW_ALLOC(sizeof*(p)))
#define AW_NEW0(p) AW_CALLOC(1, sizeof(*(p)))

#endif //INCLUDED_AW_MEMORY_H
