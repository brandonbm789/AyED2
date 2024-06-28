#include "pair.h"
#include <assert.h>

pair_t pair_new(int x, int y){
    pair_t p;
    p.values[0] = x;
    p.values[1] = y;
    assert(p.values[0] == x && p.values[1] == y);
    return p;
}

int pair_first(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    return p.values[0];
}

int pair_second(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    return p.values[1];
}

pair_t pair_swapped(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    pair_t q;
    q.values[0] = p.values[1];
    q.values[1] = p.values[0];
    assert(q.values[0] == p.values[1] && q.values[1] == p.values[0]);
    return q;
}

pair_t pair_destroy(pair_t p){
    return p;
}
