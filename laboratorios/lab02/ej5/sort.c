#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int i = izq +1u;
    unsigned int j = der;
    unsigned int ppiv = izq;
    while(i <= j){
        if(goes_before(a[i], a[ppiv])){
            i++;
        }else if(goes_before(a[ppiv], a[j])){
            j--;
        }else if( !goes_before(a[i], a[ppiv]) && !goes_before(a[ppiv], a[j])){
            swap(a, i, j);
            i++;
            j--;
        }else{}
    }
    swap(a, ppiv, j);
    ppiv = j;
    for(unsigned int i = izq; i < ppiv; i++){
        goes_before(a[i], a[ppiv]);
    }
    for(unsigned int j = ppiv + 1; j <= der; j++){
        goes_before(a[ppiv], a[j]);
    }
    
    return ppiv;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;
    if (der > izq){ 
        ppiv = partition(a,izq,der);
        if(ppiv > izq){
        quick_sort_rec(a,izq,ppiv-1);
        }
        if(ppiv < der){
        quick_sort_rec(a,ppiv+1,der);
        }
                    }
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}


