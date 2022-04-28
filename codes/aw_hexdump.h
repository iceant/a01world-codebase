//
// Created by pengc on 2022/4/28.
//

#ifndef INCLUDED_AW_HEXDUMP_H
#define INCLUDED_AW_HEXDUMP_H

#ifndef INCLUDED_AW_TYPES_H
#include <aw_types.h>
#endif // INCLUDED_AW_TYPES_H

#ifndef INCLUDED_STDIO_H
#define INCLUDED_STDIO_H
#include <stdio.h>
#endif // INCLUDED_STDIO_H


void aw_hexdump(FILE *stream, const void* data, aw_size_t size);

#endif //INCLUDED_AW_HEXDUMP_H
