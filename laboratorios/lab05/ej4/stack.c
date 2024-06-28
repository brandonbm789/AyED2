#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    int elem;
    stack next;
};

stack stack_empty(){
    return NULL;
}

bool stack_is_empty(stack s){
    return s == NULL;
}

stack stack_push(stack s, stack_elem e){
    stack p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->next = s;
    return p;
}

stack stack_pop(stack s){
    stack p = s;
    if(!stack_is_empty(s)){
        s = s->next;
        free(p);
    }
    return s;
}

unsigned int stack_size(stack s){
    stack p = s;
    unsigned int n = 0u;
    while(p != NULL){
        p = p->next;
        n++;
    }
    return n;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->elem;    
}

stack_elem *stack_to_array(stack s){
    unsigned int size = stack_size(s);
    stack_elem *array = calloc(size, sizeof(stack_elem));
    stack p = s;
    while(size > 0u){
        array[size - 1] = p->elem;
        p = p->next;
        size--;
    }
    return array;
}

stack stack_destroy(stack s){
    stack p = s;
    while(s != NULL){
        s = s->next;
        free(p);
        p = s;
    }
    return s;
}
