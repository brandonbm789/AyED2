#include "strfuncs.h"

#include <stdlib.h>
#include <stdio.h>

size_t string_length(const char *str){
    size_t i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

char *string_filter(const char *str, char c){
    size_t length = string_length(str);
    size_t i = 0u;
    size_t j = 0u;
    char *res = malloc(sizeof(char)*(length + 1));
    if(str == NULL){
        return NULL;
    }
    while(j < length){
        if(str[j] == c){
            j++;
        }else{
            res[i] = str[j];
            i++;
            j++;
        }
    }
    res[i] = '\0';
    return res;
}

bool string_is_symmetric(const char *str){
    size_t length = string_length(str);
    size_t i = 0u;
    size_t j = (length - 1);    
    bool b = true;
    while(i < j && b){
        if(str[i] != str[j]){
            b = false;
        }
        i++;
        j--;
    }
    return b;
}