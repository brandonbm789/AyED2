#include "pair.h"
#include <assert.h>
#include <stdlib.h>

struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y){
    pair_t p;
    p = malloc(sizeof(struct s_pair_t));
    p->fst = x;
    p->snd = y;
    assert(p->fst == x && p->snd == y);
    return p;
}

int pair_first(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    return p->fst;
}

int pair_second(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    pair_t q = malloc(sizeof(struct s_pair_t));
    q = pair_new(p->snd, p->fst);
    assert(pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p));
    return q;
}

pair_t pair_destroy(pair_t p){
    free(p);
    return NULL;
}
