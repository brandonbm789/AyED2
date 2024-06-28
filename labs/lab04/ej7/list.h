#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

typedef int list_elem;

typedef struct Node_of_int *list;

list empty(void);
/*
crea una lista vacia
*/

list addl(list_elem e, list l);
/*
agrega un elemento al principio de la lista
*/

bool is_empty(list l);
/*
devuelve true si l es vacia
*/

list_elem head(list l);
/*
devuelve el primer elemento de la lista
PRECONDICION: !is_empty(l)
*/

list tail(list l);
/*
elimina el primer elemento de la lista
PRECONDICION: !is_empty(l)
*/

list addr(list_elem e, list l);
/*
agrega un elemento al final de la lista
*/

unsigned int length(list l);
/*
devuelve la longitud de la lista
*/

list concat(list l1, list l2);
/*
agrega al final de l1 todos los elementos de l2
*/

list_elem index(list l, unsigned int n);
/*
devuelve el elemento de l en la posicion n
PRECONDICION: length(l) > n
*/

list take(list l, unsigned int n);
/*
deja solo los primeros n elementos de l en l
*/

list drop(list l, unsigned int n);
/*
elimina de l los primeros n elementos
*/

list copy_list(list l);
/*
devuelve una copia de la lista l
*/

list destroy(list l);
/*
libera la memoria reservada por la lista si es necesario
*/

#endif
