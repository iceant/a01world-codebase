//
// Created by pengc on 2022/4/29.
//

#include <aw_hashtable.h>
#include <aw_types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static aw_uint32_t hashfn_fmix32(uint32_t h) {
    h ^= h >> 16;
    h *= 0x3243f6a9U;
    h ^= h >> 16;
    return h;
}

static aw_uint32_t string_hash(const void *data, void *arg) {
    //djb2
    aw_uint32_t hash = (const aw_uint32_t) 5381;
    const char *str = (const char*) data;
    char c;
    while((c=*str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hashfn_fmix32(hash);
}

static void* string_cp(const void *data, void *arg) {
    const char *input = (const char*) data;
    size_t input_length = strlen(input) + 1;
    char *result;
    result = malloc(sizeof(*result) * input_length);
    if (NULL==result) {
        fprintf(stderr,"malloc() failed in file %s at line # %d", __FILE__,__LINE__);
        exit(EXIT_FAILURE);
    }
    strcpy(result, input);
    return result;
}

static void* integer_cp(const void* data, void* arg){
    return (void*)data;
}

static bool integer_eq(const void *data1, const void* data2, void* arg){
    return ((int)data1)==((int)data2);
}

static void integer_free(void* data, void* arg){
}

static bool string_eq(const void *data1, const void *data2, void *arg) {
    const char *str1 = (const char*) data1;
    const char *str2 = (const char*) data2;
    return !(strcmp(str1, str2)) ? true : false;
}

static void string_free(void *data, void *arg) {
    free(data);
}

void htable_print(void* key, void* value, void* args){
    printf("%s: %s\n", (const char*)key, (const char* )value);
}

int main(int argc, char ** argv){
    aw_hashtable_key_ops keyOps;
    keyOps.hash = string_hash;
    keyOps.cp =string_cp;
    keyOps.eq = string_eq;
    keyOps.free = string_free;
    keyOps.arg = NULL;

    aw_hashtable_val_ops valOps;
    valOps.cp = string_cp;
    valOps.free = string_free;
    valOps.eq = string_eq;
    valOps.arg = NULL;

    aw_hashtable_t * htable = aw_hashtable_new(keyOps, valOps);

    aw_hashtable_put(htable, "name", "Chen Peng");
    aw_hashtable_put(htable, "age", "13");

    printf("Name: %s\n", aw_hashtable_get(htable, "name"));
    printf("Age: %s\n", aw_hashtable_get(htable, "age"));
    printf("Contains 'name'? %s\n", aw_hashtable_contains(htable, "name")?"TRUE":"FALSE");
    printf("Contains 'salary'? %s\n", aw_hashtable_contains(htable, "salary")?"TRUE":"FALSE");
    printf("Number of collisions: %d\n", aw_hashtable_numberOfCollisions(htable));

    printf("== Now foreach iterate the htable... == \n");
    aw_hashtable_foreach(htable, htable_print, NULL);

    aw_hashtable_free(&htable);

    return 0;
}