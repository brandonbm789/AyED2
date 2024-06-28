#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool invrep(stack s){
    return (s->size == stack_size(s) && s->size <= s->capacity);
}

stack stack_empty(){
    return NULL;
}

stack stack_push(stack s, stack_elem e){
    if(stack_is_empty(s)){
        s = malloc(sizeof(struct _s_stack));
        s->size = 1u;
        s->capacity = 1u;
        s->elems = calloc(s->size, sizeof(stack_elem));
        s->elems[0] = e;
    }else if(s->size == s->capacity){
        s->capacity = s->capacity * 2;
        s->size++;
        s->elems = realloc(s->elems, sizeof(stack_elem) * s->capacity);
        s->elems[s->size - 1] = e;
    }else if(s->size < s->capacity){
        s->size++;
        s->elems[s->size - 1] = e;
    }
    assert(invrep(s));
    return s;
}

stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    assert(invrep(s));
    s->size--;
    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s){
    assert(invrep(s));
    return s->size;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    assert(invrep(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s){
    return s == NULL;
    }

stack_elem *stack_to_elems(stack s){
    assert(invrep(s));
    unsigned int length = stack_size(s);
    stack_elem *only_elems = calloc(length, sizeof(stack_elem));
    for(unsigned int i = 0u; i < length; i++){
        only_elems[i] = s->elems[i];
    }
    return only_elems;
}

stack stack_destroy(stack s){
    free(s->elems);
    free(s);
    return NULL;
}