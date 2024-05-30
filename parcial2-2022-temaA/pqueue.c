#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node* front;

};

struct s_node {
    pqueue_elem e;
    unsigned int Priority;
    struct s_node* next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->e = e;
    new_node->next = NULL;
    new_node->Priority = priority;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    if(q->size > 1u){
        struct s_node* temp = q->front;
        while(temp->next != NULL){
            if(temp->Priority > temp->next->Priority){
                return false;
            }
            temp = temp->next;
        }
    }
    return true;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->size = 0u;
    q->front = NULL;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    if(pqueue_is_empty(q)|| q->front->Priority > priority){
        new_node->next = q->front; 
        q->front = new_node;
    }else{
        struct s_node* temp = q->front;
        while(temp->next != NULL && priority >= temp->next->Priority){
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {

    return q->front == NULL;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem e = q->front->e;
    assert(invrep(q));
    return e;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));    
    assert(invrep(q));
    return q->front->Priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size=0u;
    size = q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node* killme = q->front;
    q->front = q->front->next;
    killme = destroy_node(killme);
    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    while(!pqueue_is_empty(q)){
        q = pqueue_dequeue(q);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
