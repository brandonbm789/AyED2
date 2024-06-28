#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter p = malloc(sizeof(struct _counter));
    p->count = 0u;
    return p;
}

void counter_inc(counter c) {
    c->count++;
}

bool counter_is_init(counter c) {
    return c->count == 0u;
}

void counter_dec(counter c) {
    assert(!counter_is_init(c));
    c->count--;
}

counter counter_copy(counter c) {
    counter copy = malloc(sizeof(struct _counter));
    copy->count = c->count;
    return copy;
}

void counter_destroy(counter c) {
    free(c);
    c = NULL;
}
