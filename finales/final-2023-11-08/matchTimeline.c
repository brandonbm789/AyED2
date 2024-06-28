#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matchTimeline.h"

/* ============================================================================
STRUCTS
============================================================================ */

struct s_node
{
    team team;
    event e;
    time t;
    playerNumber pn;
    struct s_node *next;
};

struct s_matchTimeline
{
    struct s_node *head;
    unsigned int score_home;
    unsigned int score_away;
    unsigned int registers;
};

/* ============================================================================
INVERP & VALIDATION
============================================================================ */

static bool invrep(matchTimeline mt)
{
    if(mt == NULL){
        return false;
    }
    return true; 
}

bool matchTimeline_is_time_and_score_valid(matchTimeline mt)
{
    if(mt != NULL){
        struct s_node *temp = mt->head;
        if(temp != NULL){
            while(temp->next != NULL){
                if(temp->t > temp->next->t){
                    return false;
                }else{
                    temp = temp->next;
                }
            }
            
        }
        unsigned int score_h = 0u;
        unsigned int score_a = 0u;
        temp = mt->head;
        while(temp != NULL){
            if(temp->e == Goal){
                if(temp->team == Home){
                    score_h++;
                }else{
                    score_a++;
                }
            }
            temp = temp->next;
        }
        if(score_h != mt->score_home || score_a != mt->score_away){
            return false;
        }
        
    }else{
        return false;
    }
    return true;
}

/* ============================================================================
CONSTRUCTOR
============================================================================ */

matchTimeline matchTimeline_empty(void)
{
    matchTimeline mt = NULL;

    mt = malloc(sizeof(struct s_matchTimeline));
    mt->head = NULL;
    mt->registers = 0u;
    mt->score_away = 0u;
    mt->score_home = 0u;

    assert(invrep(mt));
    return mt;
}

/* ============================================================================
INSERTION
============================================================================ */

static struct s_node *create_node(team team, event e, time t, playerNumber pn)
{

    struct s_node *new_node = NULL;

    new_node = malloc(sizeof(struct s_node));   
    new_node->e = e;
    new_node->team = team;
    new_node->pn = pn;
    new_node->t = t;
    new_node->next = NULL;

    return new_node;
}

/* ============================================================================
GOAL
============================================================================ */

matchTimeline matchTimeline_score_goal(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    bool no_red = true;
    struct s_node *current = mt->head;
    while(current != NULL){
        if(current->e == RedCard && current->pn == pn && current->team == team){
            no_red = false;
        }
        current = current->next;
    }
    if(t <= 90u && pn > 0u && no_red){
        struct s_node *new_node = create_node(team, Goal, t, pn);
        if(mt->head == NULL){
            mt->head = new_node;
        }else{
            struct s_node *temp = mt->head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = new_node;
        }
        if(team == Home){
            mt->score_home++;
        }else{
            mt->score_away++;
        }
        mt->registers++;
    }
    return mt;
}

/* ============================================================================
THE CARDS
============================================================================ */

matchTimeline matchTimeline_receive_yellowCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    bool b = false;
    bool no_red = true;
    struct s_node *current = mt->head;
    while(current != NULL){
        if(current->e == RedCard && current->pn == pn && current->team == team){
            no_red = false;
        }
        current = current->next;
    }
    if(t <= 90u && pn > 0u && no_red){
        struct s_node *new_node = create_node(team, YellowCard, t, pn);
        if(mt->head == NULL){
            mt->head = new_node;
        }else{
            struct s_node *temp = mt->head;
            while(temp != NULL){
                if(temp->e == YellowCard && temp->pn == pn && temp->team == team){
                   b = true;
                }
                temp = temp->next;
            }
            temp = mt->head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = new_node;
        }
        mt->registers++;
        if(b){
            mt = matchTimeline_receive_redCard(mt, team, t, pn);
        }
    }

    return mt;
}

matchTimeline matchTimeline_receive_redCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    bool no_red = true;
    struct s_node *current = mt->head;
    while(current != NULL){
        if(current->e == RedCard && current->pn == pn && current->team == team){
            no_red = false;
        }
        current = current->next;
    }
    if(t <= 90u && pn > 0u && no_red){
        struct s_node *new_node = create_node(team, RedCard, t, pn);
        if(mt->head == NULL){
            mt->head = new_node;
        }else{
            struct s_node *temp = mt->head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = new_node;
        }
        mt->registers++;
    }

    return mt;
}

matchTimeline matchTimeline_receive_WhiteCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    bool no_red_or_yellow = true;
    struct s_node *current = mt->head;
    while(current != NULL){
        if((current->e == RedCard || current->e == YellowCard) && current->pn == pn && current->team == team){
            no_red_or_yellow = false;
        }
        current = current->next;
    }
    if(t > 75u && t <= 90u && pn > 0u && no_red_or_yellow){
        struct s_node *new_node = create_node(team, WhiteCard, t, pn);
        if(mt->head == NULL){
            mt->head = new_node;
        }else{
            struct s_node *temp = mt->head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = new_node;
        }
        mt->registers++;
    }
    return mt;
}


/* ============================================================================
SCORE
============================================================================ */

unsigned int matchTimeline_get_score(matchTimeline mt, team team)
{
    assert(invrep(mt));
    unsigned int score;
    if(team == Home){
        score = mt->score_home;
    }else{
        score = mt->score_away;
    }
    return score;
}

/* ============================================================================
SIZE
============================================================================ */

unsigned int matchTimeline_size(matchTimeline mt)
{
    assert(invrep(mt));

    return mt->registers;
}

/* ============================================================================
PRINT
============================================================================ */

void matchTimeline_print(matchTimeline mt)
{
    fprintf(
        stdout, "            Home %u -  %u Away \n", 
        matchTimeline_get_score(mt, Home), 
        matchTimeline_get_score(mt, Away)
    );

    struct s_node *aux = mt->head;
    while (aux != NULL)
    {
        unsigned int t = aux->t;
        char *e;
        switch (aux->e)
        {
        case Goal:
            e = "    Goal   ";
            break;
        case YellowCard:
            e = "Yellow Card";
            break;
        case RedCard:
            e = "  Red Card ";
            break;
        case WhiteCard:
            e = "White  Card";
            break;
        }
        unsigned int pn = aux->pn;

        if (aux->team == Home) {
            fprintf(stdout, "%u - %s - %u' \n", pn, e, t);
        }
        else {
            fprintf(stdout, "                   %u' - %s - %u \n", t, e, pn);
        }

        aux = aux->next;
    }
}

/* ============================================================================
ARRAY
============================================================================ */

event *matchTimeline_events_array(matchTimeline mt)
{
    event *array = NULL;
    
    array = calloc(matchTimeline_size(mt), sizeof(event));
    struct s_node *temp = mt->head;
    for(unsigned int i = 0u; i < matchTimeline_size(mt); i++){
        array[i] = temp->e;
        temp = temp->next;
    }

    return array;
}

/* ============================================================================
DESTRUCTOR!
============================================================================ */

static struct s_node *destroy_node(struct s_node *node)
{
    
    free(node);
    node = NULL;
    return node;
}

matchTimeline matchTimeline_destroy(matchTimeline mt)
{
    assert(invrep(mt));

    struct s_node *temp = mt->head;
    struct s_node *killme;
    while(temp != NULL){
        killme = temp;
        temp = temp->next;
        killme = destroy_node(killme);
    }
    free(mt);
    mt = NULL;
    return mt;
}
