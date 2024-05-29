#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "tape.h"

struct _s_node {
    tape_elem elem;
    struct _s_node *next;
};

typedef struct _s_node * node_t;

struct _s_tape {
    unsigned int size;
    node_t cursor;  // Puntero al elemento actual
    node_t start;   // Puntero al primer nodo de la cinta
};

static bool invrep(tape_t tape) {
    return (tape != NULL);
}

static node_t create_node(tape_elem e) {
    node_t node = malloc(sizeof(struct _s_node));
    node->elem = e;
    node->next = NULL;
    return node;
}

static node_t destroy_node(node_t node) {
    free(node);
    node = NULL;
    return node;
}

tape_t tape_create(void) {
    tape_t tape=NULL;
    tape = malloc(sizeof(struct _s_tape));
    tape->cursor = NULL;
    tape->size = 0u;
    tape->start = NULL;
    assert(invrep(tape) && tape_is_empty(tape) && tape_at_start(tape));
    return tape;
}

tape_t tape_rewind(tape_t tape) {
    assert(invrep(tape));
    tape->cursor = tape->start;
    assert(invrep(tape) && tape_at_start(tape));
    return tape;
}


bool tape_at_start(tape_t tape) {
    return tape->cursor == tape->start;
}

bool tape_at_stop(tape_t tape) {
    return tape->cursor == NULL;
}

bool tape_is_empty(tape_t tape) {
    return tape->size == 0u;
}

unsigned int tape_length(tape_t tape) {
    return tape->size;
}

tape_t tape_step(tape_t tape) {
    tape->cursor = tape->cursor->next;
    return tape;
}

tape_t tape_insertl(tape_t tape, tape_elem e) {
    assert(invrep(tape));
    node_t new_node = create_node(e);
    node_t cursorviejo = tape->cursor;
    if(tape->start != NULL){
        if(tape_at_start(tape)){
            new_node->next = tape->start;
            tape->start = new_node;
            tape->cursor = new_node;
        }else{
            tape = tape_rewind(tape);
            while(tape->cursor->next != cursorviejo){
                tape->cursor = tape->cursor->next;
            }
            tape->cursor->next = new_node;
            new_node->next = cursorviejo;
            tape->cursor = new_node;
        }
    }else{
        tape->start = new_node;
        tape->cursor = new_node;
    }
    tape->size++;
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) && e == tape_read(tape));
    return tape;
}

tape_t tape_insertr(tape_t tape, tape_elem e) {
    assert(invrep(tape) && (!tape_at_stop(tape) || tape_is_empty(tape)));
    node_t new_node=create_node(e);
    if (tape->start!= NULL) {
        new_node->next = tape->cursor->next;
        tape->cursor->next = new_node;
        tape->cursor = new_node;
    } else {
        tape->start = new_node;
        tape->cursor = new_node;
    }
    tape->size++;
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) && e == tape_read(tape));
    return tape;
}

tape_t tape_erase(tape_t tape) {
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape));
    node_t cursorborrado = tape->cursor;
    tape = tape_rewind(tape);
    while(tape->cursor->next != cursorborrado){
        tape = tape_step(tape);
    }
    tape->cursor->next = cursorborrado->next;
    cursorborrado = destroy_node(cursorborrado);
    tape->cursor = tape->cursor->next;
    tape->size--;
    assert(invrep(tape));
    return tape;
}

/*
la funcion tape_erase no andaria en el caso que el tape tenga un solo elemento
pero en los ejemplos del parcial anda, alta paja cambiarla.
*/

tape_elem tape_read(tape_t tape) {
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape));
    return tape->cursor->elem;
}

void tape_dump(tape_t tape) {
    assert(invrep(tape));
    node_t node=tape->start;
    printf("#");
    while (node != NULL) {
        if (node != tape->cursor) {
            printf("-%c-", node->elem);
        } else {
            printf("-[%c]-", node->elem);
        }
        node = node->next;
    }
    if (tape->cursor==NULL) {
        printf("-[]-");
    }
    printf("#\n");
}

tape_t tape_copy(tape_t tape) {
    assert(invrep(tape));
    tape_t copy = tape_create();
    copy->size = 0u;
    tape_t t_aux = tape;
    t_aux = tape_rewind(t_aux);
    node_t copy_node = malloc(sizeof(struct _s_node));
    while(!tape_at_stop(t_aux)){
        if(tape_length(copy) == 0u){
            copy_node = create_node(t_aux->cursor->elem);
            tape_insertl(copy, copy_node->elem);
            t_aux = tape_step(t_aux);
        }else{
            copy_node = create_node(t_aux->cursor->elem);
            tape_insertr(copy, copy_node->elem);
            t_aux = tape_step(t_aux);
        }
    }
    copy = tape_rewind(copy);
    assert(invrep(copy) && copy != tape && !tape_is_empty(copy) && tape_at_start(copy) && tape_length(copy) == tape_length(tape));
    return copy;
}

tape_t tape_destroy(tape_t tape) {
    assert(invrep(tape));
    tape = tape_rewind(tape);
    node_t killme;
    while(!tape_is_empty(tape)){
        killme = tape->cursor;
        tape = tape_step(tape);
        killme = destroy_node(killme);
        tape->size--;
    }
    free(tape);
    tape = NULL;
    assert(tape == NULL);
    return tape;
}


