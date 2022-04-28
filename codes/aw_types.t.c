//
// Created by pengc on 2022/4/28.
//

#include <aw_types.h>
#include <stdio.h>
#include <stdlib.h>

#define AW_PRINT_SIZE(t) printf("sizeof(%s): %d\n", #t, sizeof(t))
#define AW_PRINT_VALUE(v) printf("%s: %lld\n", #v, v)

int main(int argc, char** argv){
    printf("__STDC_VERSION__: %ld\n", __STDC_VERSION__);
    AW_PRINT_SIZE(aw_int8_t);
    AW_PRINT_SIZE(aw_int16_t);
    AW_PRINT_SIZE(aw_int32_t);
    AW_PRINT_SIZE(aw_int64_t);

    AW_PRINT_SIZE(aw_uint8_t);
    AW_PRINT_SIZE(aw_uint16_t);
    AW_PRINT_SIZE(aw_uint32_t);
    AW_PRINT_SIZE(aw_uint64_t);

    AW_PRINT_SIZE(aw_size_t);
    AW_PRINT_SIZE(aw_bool_t);

    AW_PRINT_VALUE(AW_INT8_MIN);
    AW_PRINT_VALUE(AW_INT8_MAX);
    AW_PRINT_VALUE(AW_INT16_MIN);
    AW_PRINT_VALUE(AW_INT16_MAX);
    AW_PRINT_VALUE(AW_INT32_MIN);
    AW_PRINT_VALUE(AW_INT32_MAX);
    AW_PRINT_VALUE(AW_INT64_MIN);
    AW_PRINT_VALUE(AW_INT64_MAX);

    AW_PRINT_VALUE(AW_UINT8_MAX);
    AW_PRINT_VALUE(AW_UINT16_MAX);
    AW_PRINT_VALUE(AW_UINT32_MAX);
    printf("AW_UINT64_MAX: %llu\n", AW_UINT64_MAX);

    return 0;
}