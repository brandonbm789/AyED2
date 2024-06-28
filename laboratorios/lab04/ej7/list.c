#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct Node_of_int{
    list_elem elem;
    struct Node_of_int *next;
};

list empty(void){
    list l = NULL;
    return l;
}

list addl(list_elem e, list l){
    list l1 = malloc(sizeof(struct Node_of_int));
    l1->elem = e;
    l1->next = l;
    l = l1;
    return l;
}

list destroy(list l){
    list p = NULL;
    while(l != NULL){
        p = l;
        l = l->next;
        free(p);
    }

    return l;
}

bool is_empty(list l){
    return (l == NULL);
}

list_elem head(list l){
    assert(!is_empty(l));
    return l->elem;
}

list tail(list l){
    assert(!is_empty(l));
    list p = l;
    l = l->next;
    free(p);
    return l;
}

list addr(list_elem e, list l){
    list q = malloc(sizeof(struct Node_of_int));
    q->elem = e;
    q->next = NULL;
    if(!is_empty(l)){
        list p = l;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = q;
    }else{
        l = q;
    }
    return l;
}

unsigned int length(list l){
    unsigned int n = 0u;
    list p = l;
    while(!is_empty(p)){
        n++;
        p = p->next;
    }
    return n;
}

list concat(list l1, list l2){
    list p = l1;
    if(p == NULL){
        l1 = l2;
    }else{
        while(p->next != NULL){
            p = p->next;
        }
        p->next = l2;
        }
    return l1;
}

list_elem index(list l, unsigned int n){
    assert(length(l) > n);
    list p = l;
    for(unsigned int i = 1u; i < n; i++){
        p = p->next;
    }
    return p->elem;
}

list take(list l, unsigned int n){
    list p = l;
    list q;
    if(!is_empty(p)){
        if(n == 0){destroy(l);}
        else{
            for(unsigned int i = 0u; i < n && p!= NULL; i++){
                p = p->next;
            }
            while(p != NULL){
                q = p;
                p = p->next;
                free(q);
            }
        }
    }
    return l;
}


list drop(list l, unsigned int n){
    list p = NULL;
    for(unsigned int i = 0u; i < n && !is_empty(l); i++){
        p = l;
        l = l->next;
        free(p);
    }
    return l;
}

list copy_list(list l){
    list copy = empty();
    list p = l;
    while(!is_empty(p)){
        copy = addr(p->elem, copy);
        p = p->next;

    }
    return copy;
}