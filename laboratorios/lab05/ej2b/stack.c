#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    int elem;
    stack next;
    unsigned int size;
};

bool invrep(stack s){
    if(!stack_is_empty(s)){
        return (s->size == stack_size(s));
    }else{
        return (0u == stack_size(s));
    }
}

stack stack_empty(){
    return NULL;
    assert(invrep(NULL));
}

bool stack_is_empty(stack s){
    return s == NULL;
}

stack stack_push(stack s, stack_elem e){
    assert(invrep(s));
    stack p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->next = s;
    if(stack_is_empty(s)){
        p->size = 1u;
    }else{
        p->size = s->size++;
    }
    assert(invrep(p));
    return p;
}

stack stack_pop(stack s){
    assert(invrep(s));
    stack p = s;
    if(!stack_is_empty(s)){
        s = s->next;
        free(p);
    }
    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s){
    if(stack_is_empty(s)){
        return 0u;
    }
        return s->size;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->elem;    
}

stack_elem *stack_to_array(stack s){
    assert(invrep(s));
    unsigned int size = stack_size(s);
    stack_elem *array = calloc(size, sizeof(stack_elem));
    stack p = s;
    while(size > 0u){
        array[size - 1] = p->elem;
        p = p->next;
        size--;
    }
    assert(invrep(p));
    return array;
}

stack stack_destroy(stack s){
    assert(invrep(s));
    stack p = s;
    while(s != NULL){
        s = s->next;
        free(p);
        p = s;
    }
    assert(invrep(s));
    return s;
}
