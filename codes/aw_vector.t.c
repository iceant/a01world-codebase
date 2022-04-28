//
// Created by pengc on 2022/4/28.
//

#include <aw_vector.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    aw_vector_t * vector = aw_vector_new(10);

    for(int i=0; i< aw_vector_capacity(vector); i++){
        aw_vector_append(vector, (void*)i);
    }

    aw_vector_hexdump(vector, stdout);

    for(int i=0; i< aw_vector_capacity(vector); i++){
        int value = (int) aw_vector_get(vector, i);
        printf("Value: %d\n", value);
    }

    for(int i=0; i< 10; i++){
        aw_vector_append(vector, 0);
    }

    aw_vector_hexdump(vector, stdout);

    aw_vector_free(&vector);

    return 0;
}