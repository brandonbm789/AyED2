#include "dna.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef TEST

int main()
{
    dna_t dna = dna_A();
    dna_t dna2 = dna_T();
    dna_t dna3 = dna_G();
    dna = dna_join(dna, dna2);
    dna_print(dna);
    dna = dna_join(dna, dna3);
    dna_print(dna);
    dna_t *array = dna_cut(dna, 2);
    printf("array:\n");
    dna_print(array[0]);
    dna_print(array[1]);
    dna_t dna4 = dna_A();
    dna_t dna5 = dna_T();
    dna_t dna6 = dna_G();
    dna4 = dna_join(dna4, dna5);
    dna4 = dna_join(dna4, dna6);
    if(dna_is_equal(dna4, dna)){
        printf("son iguales\n");
    }else{
        printf("no son iguales\n");
    }
    dna_t dna7 = dna_C();
    dna4 = dna_join(dna4, dna7);
    if(dna_is_prefix(dna, dna4)){
        printf("es prefijo\n");
    }else{
        printf("no es prefijo\n");
    }
    dna = dna_destroy(dna);
    dna2 = dna_destroy(dna2);
    dna3 = dna_destroy(dna3);
    dna4 = dna_destroy(dna4);
    dna5 = dna_destroy(dna5);
    dna6 = dna_destroy(dna6);
    dna7 = dna_destroy(dna7);
    dna_destroy(array[0]);
    dna_destroy(array[1]);
    free(array);

    return (0);
}

#endif
