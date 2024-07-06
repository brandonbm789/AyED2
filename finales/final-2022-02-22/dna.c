#include "dna.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct _node {
    nucleobase_t elem;
    struct _node *next;
};

struct _dna_t
{
    struct _node* chain;
    unsigned int lenght;
};

static struct _node* single_node(nucleobase_t e)
{
    struct _node *node = calloc(1, sizeof(struct _node));
    assert(node != NULL);
    node->elem = e;
    node->next = NULL;
    return (node);
}

dna_t dna_T()
{
    dna_t res = NULL;
    res = malloc(sizeof(struct _dna_t));
    res->lenght = 1u;
    struct _node *new_node = single_node(T);
    res->chain = new_node;
    return res;
}

dna_t dna_C()
{
    dna_t res = NULL;
    res = malloc(sizeof(struct _dna_t));
    res->lenght = 1u;
    struct _node *new_node = single_node(C);
    res->chain = new_node;
    return res;
}

dna_t dna_A()
{
    dna_t res = NULL;
    res = malloc(sizeof(struct _dna_t));
    res->lenght = 1u;
    struct _node *new_node = single_node(A);
    res->chain = new_node;
    return res;
}

dna_t dna_G()
{
    dna_t res = NULL;
    res = malloc(sizeof(struct _dna_t));
    res->lenght = 1u;
    struct _node *new_node = single_node(G);
    res->chain = new_node;
    return res;
}


dna_t dna_join(dna_t first, dna_t second)
{
    dna_t res = NULL;
    res = first;
    struct _node *temp = second->chain;
    struct _node *current = res->chain;
    if(current != NULL){
        while(current->next != NULL){
            current = current->next;
        }
        while(temp != NULL){
            current->next = single_node(temp->elem);
            current = current->next;
            temp = temp->next;
        }
    }else{
        res->chain = single_node(temp->elem);
        current = res->chain;
        while(temp != NULL){
            current->next = single_node(temp->elem);
            current = current->next;
            temp = temp->next;
        }
    }
    res->lenght = first->lenght + second->lenght;

    return res;
}

unsigned int dna_length(dna_t dna)
{
    unsigned int res = 0u;
    res = dna->lenght;
    return res;
}

void dna_print(dna_t dna)
{
    struct _node *temp = dna->chain;
    printf("( ");
    for(unsigned int i = 0u; i < dna->lenght; i++){
        if(temp->elem == 0){
            printf("T");
        }else if(temp->elem == 1){
            printf("C");
        }else if(temp->elem == 2){
            printf("A");
        }else if(temp->elem == 3){
            printf("G");
        }
        temp = temp->next;
    }
    printf(" )\n");
}

bool dna_is_prefix(dna_t first, dna_t second)
{
    bool is_prefix = false;
    if(first != NULL && second != NULL){
        is_prefix = true;
        struct _node *temp2 = second->chain;
        struct _node *temp1 = first->chain;
        if(temp2 != NULL && temp1 != NULL){
            while(temp2->elem != temp1->elem){
                temp2 = temp2->next;
                if(temp2 == NULL){
                    return false;
                }
            }
            while(temp2 != NULL && temp1 != NULL && is_prefix){
                if(temp2->elem != temp1->elem){
                    is_prefix = false;
                }
                temp2 = temp2->next;
                temp1 = temp1->next;
            }
            if(temp2 == NULL && temp1 != NULL){
                is_prefix = false;
            }
        }
    }
    return is_prefix;
}

bool dna_is_equal(dna_t first, dna_t second)
{
    bool is_equal = false;
    is_equal = dna_length(first) == dna_length(second) && dna_is_prefix(first, second) && dna_is_prefix(second, first);
    return is_equal;
}

dna_t *dna_cut(dna_t dna, unsigned int count)
{
    assert(count > 0 && count < dna_length(dna));
    dna_t* res = NULL;
    res = calloc(2, sizeof(dna_t));
    struct _node *temp1 = dna->chain;
    res[0] = malloc(sizeof(struct _dna_t));
    res[1] = malloc(sizeof(struct _dna_t));
    struct _node *temp2 = NULL;

    for(unsigned int i = 0u; i < count; i++){
        struct _node *new_node = single_node(temp1->elem);
        if(temp2 == NULL){
            res[0]->chain = new_node;
        }else{
            temp2->next = new_node;
        }
        temp2 = new_node;
        temp1 = temp1->next;
    }

    temp2 = NULL;
    for(unsigned int i = 0u; i < dna_length(dna) - count; i++){
        struct _node *new_node = single_node(temp1->elem);
        if(temp2 == NULL){
            res[1]->chain = new_node;
        }else{
            temp2->next = new_node;
        }
        temp2 = new_node;
        temp1 = temp1->next;
    }
    res[0]->lenght = count;
    res[1]->lenght = dna_length(dna) - count;
    
    return res;
}

dna_t dna_destroy(dna_t dna)
{
    struct _node *killme;
    while(dna->chain != NULL){
        killme = dna->chain;
        dna->chain = dna->chain->next;
        free(killme);
    }
    free(dna);
    dna = NULL;
    return dna;
}
