//
// Created by pengc on 2022/4/28.
//

#ifndef INCLUDED_AW_TYPES_H
#define INCLUDED_AW_TYPES_H

#ifndef __STDC__
#error Not a standard C compiler.
#endif

#if (__STDC_VERSION__ >= 199901L)

#ifndef INCLUDED_STDINT_H
#define INCLUDED_STDINT_H
#include <stdint.h>
#endif // INCLUDED_STDINT_H

#ifndef INCLUDED_STDBOOL_H
#define INCLUDED_STDBOOL_H
#include <stdbool.h>
#endif // INCLUDED_STDBOOL_H

////////////////////////////////////////////////////////////////////////////////
////
typedef int8_t aw_int8_t;
typedef int16_t aw_int16_t;
typedef int32_t aw_int32_t;
typedef int64_t aw_int64_t;

typedef uint8_t aw_uint8_t;
typedef uint16_t aw_uint16_t;
typedef uint32_t aw_uint32_t;
typedef uint64_t aw_uint64_t;

typedef size_t aw_size_t;

typedef bool aw_bool_t;
#define AW_TRUE true
#define AW_FALSE false

#define AW_INT8_MIN INT8_MIN
#define AW_INT8_MAX INT8_MAX

#define AW_INT16_MIN INT16_MIN
#define AW_INT16_MAX INT16_MAX

#define AW_INT32_MIN INT32_MIN
#define AW_INT32_MAX INT32_MAX

#define AW_INT64_MIN INT64_MIN
#define AW_INT64_MAX INT64_MAX

#define AW_UINT8_MAX UINT8_MAX
#define AW_UINT16_MAX UINT16_MAX
#define AW_UINT32_MAX UINT32_MAX
#define AW_UINT64_MAX UINT64_MAX

#else /* __STDC__ defined but not __STD_VERSION__ */
#error __STDC__ defined but not __STD_VERSION__
#endif


////////////////////////////////////////////////////////////////////////////////
////



#endif //INCLUDED_AW_TYPES_H
