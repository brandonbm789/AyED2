#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "cf_match.h"

struct _s_match {
    card carta;
    struct _s_match *next;
};

cf_match match_new(void)
{
    return NULL;
}

cf_match match_add(cf_match match, card c)
{
    cf_match new = malloc(sizeof(struct _s_match));
    new->carta = c;
    new->next = NULL;
    if(match == NULL){
        match = new;
    }else{
        cf_match temp = match;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new;
    }
    return match;
}

unsigned int match_size(cf_match match)
{
    unsigned int size = 0u;
    if(match != NULL){
        cf_match temp = match;
        while(temp != NULL){
            size++;
            temp = temp->next;
        }
    }
    return size;
}

bool is_match_correct(cf_match match)
{
    bool res = true;
    if(match == NULL){
        res = false;
    }else{
        if(card_player(match->carta) != 1){
            res = false;
        }else{
            if(match_size(match) % 2 != 0){
                res = false;
            }else{
                cf_match temp = match;
                while(temp->next != NULL && res){
                    if(card_player(temp->carta) == card_player(temp->next->carta) || card_color(temp->carta) == card_color(temp->next->carta)){
                        res = false;
                    }
                    temp = temp->next;
                }

            }

        }
    }
    return(res);
}

static int player_score(cf_match match, unsigned int player)
{
    int points = 0;
    cf_match temp = match;
    bool Flush = false;
    bool ascFlush = false;
    if(match != NULL){
        if(temp->next != NULL){
            if(card_number(temp->carta) == card_number(temp->next->carta)-1){
                if(card_player(temp->next->carta) == player){
                    points += 5;
                }
                Flush = true;
                ascFlush = true;
                temp = temp->next;
                while(temp->next != NULL){
                    if(card_number(temp->carta) == card_number(temp->next->carta)-1){
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                        Flush = true;
                        ascFlush = true;
                    }else if(card_number(temp->carta) == card_number(temp->next->carta)+1){
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                        ascFlush = false;
                        Flush = true;
                    }else if(card_number(temp->carta) == card_number(temp->next->carta)){
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                    }else{
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                        ascFlush = false;
                        Flush = false;
                    }
                    temp = temp->next;
                }
            }else if(card_number(temp->carta) == card_number(temp->next->carta)+1){
                if(card_player(temp->next->carta) == player){
                    points += 5;
                }
                Flush = true;
                ascFlush = false;
                temp = temp->next;
                while(temp->next != NULL){
                    if(card_number(temp->carta) == card_number(temp->next->carta)-1){
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                        Flush = true;
                        ascFlush = true;
                    }else if(card_number(temp->carta) == card_number(temp->next->carta)+1){
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                        ascFlush = false;
                        Flush = true;
                    }else if(card_number(temp->carta) == card_number(temp->next->carta)){
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                    }else{
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                        ascFlush = false;
                        Flush = false;
                    }
                    temp = temp->next;
                }
            }else{
                Flush = false;
                ascFlush = false;
                temp = temp->next;
                while(temp->next != NULL){
                    if(card_number(temp->carta) == card_number(temp->next->carta)-1){
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                        Flush = true;
                        ascFlush = true;
                    }else if(card_number(temp->carta) == card_number(temp->next->carta)+1){
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                        ascFlush = false;
                        Flush = true;
                    }else if(card_number(temp->carta) == card_number(temp->next->carta)){
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                    }else{
                        if(card_player(temp->next->carta) == player){
                            points += card_drop_points(temp->carta, temp->next->carta, Flush, ascFlush);
                        }
                        ascFlush = false;
                        Flush = false;
                    }
                    temp = temp->next;
                }
            }
        }
        
    } 
    return points;
}

/*
horrible pero funciona.
*/

unsigned int match_winner(cf_match match)
{
    int res;
    if(!is_match_correct(match)){
        return -1;
    }else{
        if(player_score(match, 1) > player_score(match, 2)){
            res = 1;
        }else if(player_score(match, 1) < player_score(match, 2)){
            res = 2;
        }else{
            res = 0;
        }
    }
    return res;
}

unsigned int winner_total_points(cf_match match)
{
    if (!is_match_correct(match)) {
        return -1;
    }

    int playerOneScore = player_score(match, 1);
    int playerTwoScore = player_score(match, 2);

    if (playerOneScore == playerTwoScore) {
        return 0;
    }
    return playerOneScore > playerTwoScore ? playerOneScore : playerTwoScore;
}

card* match_to_array(cf_match match)
{
    card *array = calloc(match_size(match), sizeof(card));
    cf_match temp = match;
    unsigned int i = 0u;
    while(temp != NULL){
        array[i] = temp->carta;
        temp = temp->next;
        i++;
    }
    return array;
}

void match_dump(cf_match match)
{
    card* array = match_to_array(match);
    for (unsigned int i = 0u; i < match_size(match); i++) {
        card_dump(array[i]);
    }
    free(array);
}

cf_match match_destroy(cf_match match)
{
    cf_match killme;
    while(match != NULL){
        killme = match;
        match = match->next;
        killme->carta = card_destroy(killme->carta);
        free(killme);
    }
    match = NULL;
    return match;
}
