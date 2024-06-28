#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

static
void show_pair(pair_t p) {
    printf("(%d, %d)\n", pair_first(p), pair_second(p));
}


int main(void) {
    pair_t p, q;
    // Nuevo par p
    p = pair_new(3, 4);
    // Se muestra el par por pantalla
    printf("p = ");
    show_pair(p);
    // Nuevo para q con elementos de p intercambiados
    q = pair_swapped(p);
    // Se muestra q
    printf("q = ");
    show_pair(q);
    // Se destruyen p y q
    p = pair_destroy(p);
    q = pair_destroy(q);
    return EXIT_SUCCESS;
}

/*
1. Falla porque show_pair rompe la abstraccion solo pudiendo usarse si los pair_t son tuplas
3. El diseño del pair_a-tuple no logra el encapsulamiento ya que solo funcionaba con la implementacion con tuplas.
si le lograra el encapsulamiento deberia andar sin necesidad de modificar la funcion si se cambia la implementacion, si se cambia la funcion show_pair
para que use las funciones de pair_first y pair_second se consigue el encapsulamiento.
*/