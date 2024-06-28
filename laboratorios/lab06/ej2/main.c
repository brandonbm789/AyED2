#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

int main(){
    string str1 = string_create("bronca");
    string str2 = string_create("dolor");

    if(string_less(str1, str2)){
        printf("%s es menor que %s\n", string_ref(str1), string_ref(str2));
    }else{
        printf("%s no es menor que %s\n", string_ref(str1), string_ref(str2));
    }

    str1 = string_destroy(str1);
    str2 = string_destroy(str2);

    str1 = string_create("igualdad");
    str2 = string_create("igualdad");

    if(string_eq(str1, str2)){
        printf("%s es igual que %s\n", string_ref(str1), string_ref(str2));
    }else{
        printf("%s no es igual que %s\n", string_ref(str1), string_ref(str2));
    }

    str1 = string_destroy(str1);
    str2 = string_destroy(str2);

    return 0;
}