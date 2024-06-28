#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", sizeof(messi.name),
           sizeof(messi.age), sizeof(messi.height), sizeof(messi));

    printf("La direccion de memoria de messi.name es %p\n", (void *) &messi.name);
    printf("El indice de memoria de messi.name es %lu\n", (uintptr_t) &messi.name);
    printf("La direccion de memoria de messi.age es %p\n", (void *) &messi.age);
    printf("El indice de memoria de messi.age es %lu\n", (uintptr_t) &messi.age);
    printf("La direccion de memoria de messi.height es %p\n", (void *) &messi.height);
    printf("El indice de memoria de messi.height es %lu\n", (uintptr_t) &messi.height);
    printf("La direccion de memoria de messi es %p\n", (void *) &messi);
    printf("El indice de memoria de messi es %lu\n", (uintptr_t) &messi);
    
    return EXIT_SUCCESS;
}

/*
la suma del tamanio de memoria de cada miembro es diferente del tamanio total de la estructura.
el tamanio del campo name depende de su definicion en la estructura
se definio como typedef char name_t [NAME_MAXSIZE] con NAME_MAXSIZE = 30, por lo que 
la cantidad de memoria reservada es de 30 bytes, si se cambia el NAME_MAXSIZE se cambiara
el tamanio del campo name.
la direccion de memoria del campo name es la misma que la de la estructura entera, los demas
campos si ya varian en un numero en la 3ra posicion menos significativa y entre .age y .heigth
solo se diferencia en 4 la direccion de memoria.
esto quiere decir: el campo name tiene reservado 30 bytes, pero por alguna razon se guararon 2 bytes extra reservados
para ese campo, por lo q la siguiente direccion esta 32 bytes despues, la cual es .age que tiene reservados 4 bytes,
por lo que la siguiente direccion, la .heigth se encuentra 4 bytes despues. 
el campo que tiene 2 bytes "fantasma" es la de name, o la de la estructura ya que son la misma.
*/

