#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int length = 0;
    while(s[length] != '\0' && length < FIXSTRING_MAX){
        length++;
    }
    return length;
    
}

bool fstring_eq(fixstring s1, fixstring s2) {
    unsigned int i = 0;
    while(s1[i] != '\0' && s2[i] != '\0' && i < FIXSTRING_MAX){
        if(s1[i] != s2[i]){
            return false;
        }
        i++;
    }

    if(s1[i] == '\0' && s2[i] == '\0'){
        return true;
    }

    return false;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    unsigned int i = 0;
    while(s1[i] != '\0' && s2[i] != '\0' && i < FIXSTRING_MAX){
        if(s1[i] < s2[i]){
            return true;
        }
        if(s1[i] > s2[i]){
            return false;
        }
        i++;
    }

    if(s1[i] == '\0' || i == FIXSTRING_MAX){
        return true;
    }

    return false;
    
}

