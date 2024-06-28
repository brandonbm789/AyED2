#ifndef STRFUNCS_H
#define STRFUNCS_H

#include <stdbool.h>
#include <stddef.h>

size_t string_length(const char *str);
/*
calcula la longitud de la cadena apuntada por str.
*/

char *string_filter(const char *str, char c);
/*
devuelva una nueva cadena en memoria dinamica que se obtiene
tomando los caracteres de la cadena apuntada por
str que son distintos del caracter c.
*/

bool string_is_symmetric(const char *str);
/*
indica si la cadena apuntada por str es simetrica en cuanto
a que el primer caracter es igual que el ultimo, el segundo
es igual al penultimo y asi.
*/


#endif
