#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include "card.h"

struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

static bool
invrep(card_t c) {
    // Invariante de representación
    bool valid=false;
    valid = c != NULL;
    if(c != NULL && (c->num > 9u || c->color < 0 || c->color > 3 || c->type < 0 || c->type > 2)){
        valid = false;
    }
    return valid;
}

card_t
card_new(unsigned int num, color_t color, type_t s) {
    assert((num < 10) &&
       (color==red || color==green || color==blue || color==yellow) &&
        (s==normal  || s==change_color || s==skip));
    card_t card=NULL;
    card = malloc(sizeof(struct s_card));
    card->color = color;
    card->num = num;
    card->type = s;
    assert(invrep(card));
    return card;
}


type_t
card_get_number(card_t card) {
    assert(invrep(card));
    return card->num;
}

color_t
card_get_color(card_t card) {
    assert(invrep(card));
    return card->color;
}

type_t
card_get_type(card_t card) {
    assert(invrep(card));
    return card->type;
}

bool
card_samecolor(card_t c1, card_t c2) {
    assert(invrep(c1) && invrep(c2));
    return c1->color == c2->color;
}


bool
card_samenum(card_t c1, card_t c2) {
    assert(invrep(c1) && invrep(c2));
    return c1->num == c2->num;
}

bool
card_compatible(card_t new_card, card_t pile_card) {
    bool compatible=false;
    assert(invrep(new_card) && invrep(pile_card));
    if(card_get_color(new_card) == card_get_color(pile_card)){
        compatible = true;
    }
    if(card_get_type(new_card) == change_color){
        compatible = true;
    }
    if(card_get_type(new_card) == normal && card_get_type(pile_card) == normal){
        if(card_get_number(new_card) == card_get_number(pile_card) || card_get_color(new_card) == card_get_color(pile_card)){
            compatible = true;
        }
    }
    if(card_get_type(new_card) == skip){
        if(card_get_color(new_card) == card_get_color(pile_card) || card_get_type(pile_card) == skip){
            compatible = true;
        }
    }
    return compatible;
}

card_t
card_destroy(card_t card) {
    free(card);
    card = NULL;
    return card;
}


