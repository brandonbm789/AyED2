#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include <stdio.h>

int main(){
    stack s = stack_empty();
    s = stack_push(s, 10);
    unsigned int length = stack_size(s);
    printf("la pila tiene %u elementos\n", length);
    s = stack_pop(s);
    length = stack_size(s);
    printf("despues del pop quedan %u elementos\n", length);
    s = stack_push(s, 10);
    length = stack_size(s);
    printf("despues del push hay %u elementos\n", length);
    stack_elem *array;
    s = stack_pop(s);
    array = stack_to_array(s);
    length = stack_size(s);
    printf("[");
    for(unsigned int i = 0u; i < length; i++){
        printf(" %d,", array[i]);
    }
    printf("]\n");
    for(unsigned int i = 0u; i < 10; i++){
        s = stack_push(s, i + 1);
    }
    length = stack_size(s);
    array = stack_to_array(s);
    printf("[");
    for(unsigned int i = 0u; i < length; i++){
        printf(" %d", array[i]);
        if(i < length - 1){
            printf(",");
        }
    }
    printf("]\n");

    
    return 0;
}