#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"
#include <stdio.h>

#define MAX_PRIORITY 10

struct s_pstack {
    unsigned int max_priority;
    unsigned int size;
    struct s_node *array[MAX_PRIORITY];
};

struct s_node {
    unsigned int data;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    new_node->data = e;
    new_node->next = NULL;
    assert(new_node!=NULL);
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}


static bool invrep(pstack s) {
    return s != NULL;
}

pstack pstack_empty(priority_t max_priority) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->max_priority = max_priority;
    s->size = 0u;
    for(unsigned int i = 0u; i <= max_priority; i++){
        s->array[i] = NULL;
    }
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    if(priority > s->max_priority){
        printf("se intenta ingresar un elemento con prioridad mayor a la permitida\n");
        return s;
    }else{        
        struct s_node *new_node = create_node(e);
        struct s_node* temp = s->array[priority];
        s->array[priority] = new_node;
        new_node->next = temp;
        s->size++;
    }
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    if(s->size == 0u){
        return true;
    }
    return 0u;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t max = 0u;
    for(unsigned int i = 0u; i <= s->max_priority; i++){
        if(s->array[i] != NULL){
            if(i > max){
                max = i;
            }
        }
    }
    pstack_elem e = s->array[max]->data;
    return e;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t max = 0u;
    for(unsigned int i = 0u; i <= s->max_priority; i++){
        if(s->array[i] != NULL){
            if(i > max){
                max = i;
            }
        }
    }
    return max;
}

size_t pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t killme = pstack_top_priority(s);
    if(s->array[killme]->next == NULL){
        s->array[killme] = destroy_node(s->array[killme]);
    }else{
        struct s_node* sig = s->array[killme]->next;
        s->array[killme] = destroy_node(s->array[killme]);
        s->array[killme] = sig;
    }
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    while(!pstack_is_empty(s)){
        pstack_pop(s);
    }
    free(s);
    s = NULL;
    return s;
}
