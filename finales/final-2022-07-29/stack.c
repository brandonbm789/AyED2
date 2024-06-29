#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct s_node {
    stack_elem array[CHUNK_CAPACITY];
    size_t used;
    struct s_node *next;
};

struct _s_stack {
    struct s_node *top;
    size_t size;
};

static bool
valid_chunks(stack s) {
    bool valid=true;
    struct s_node *check=s->top;
    if (check!=NULL) {
        while(check!= NULL){
            if(check->used == 0){
                return false;
            }
            check = check->next;
        }
        check = s->top;
        while(check->next != NULL){
            if(check->next->used != CHUNK_CAPACITY){
                return false;
            }
            check = check->next;
        }
    }
    return valid;
}

static bool
invrep(stack s) {
    return (s!=NULL && valid_chunks(s));
}

static struct s_node *
create_node(void) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    new_node->used = 0u;
    new_node->next = NULL;
    return new_node;
}


static struct s_node *
destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}

stack stack_empty(void) {
    stack s = NULL;
    s = malloc(sizeof(struct _s_stack));
    s->size = 0u;
    s->top = NULL;
    assert(invrep(s) && stack_is_empty(s));
    return s;
}


stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    if(s->top == NULL || s->top->used == CHUNK_CAPACITY){
        struct s_node *new_node = create_node();
        new_node->array[new_node->used] = e;
        new_node->next = s->top;
        new_node->used++;
        s->top = new_node;
    }else{
        if(s->top->used != CHUNK_CAPACITY){
            s->top->array[s->top->used] = e;
            s->top->used++;
        }
    }
    s->size++;
    assert(invrep(s) && !stack_is_empty(s));
    return s;
}


stack stack_pop(stack s) {
    assert(invrep(s) && !stack_is_empty(s));
    if(s->top->used == 1u){
        struct s_node *killme = s->top;
        s->top = s->top->next;
        killme = destroy_node(killme);
    }else{
        s->top->used--;
    }
    s->size--;
    assert(invrep(s));
    return s;
}


unsigned int stack_size(stack s) {
    assert(invrep(s));
    return s->size;
}

void stack_top(stack s, stack_elem *top) {
    assert(invrep(s) && !stack_is_empty(s) && top != NULL);
    *top = s->top->array[s->top->used-1];
}


bool stack_is_empty(stack s) {
    assert(invrep(s));
    return s->size == 0u;
}

stack_elem *stack_to_array(stack s) {
    stack_elem *array = calloc(s->size, sizeof(stack_elem));
    struct s_node *temp = s->top;
    size_t count = temp->used;
    for(unsigned int i = s->size; i > 0u; i--){
        if(count == 0u){
            temp = temp->next;
            count = temp->used;
        }else{
            array[i - 1] = temp->array[count-1];
            count--;
        }
    }
    return array;
}


stack stack_destroy(stack s) {
    struct s_node *killme;
    while(s->top != NULL){
        killme = s->top;
        s->top = s->top->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    return s;
}

