#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "cn_match.h"
#include "card.h"

struct _s_match {
  card card;
  struct _s_match *next;
};

cn_match match_new(void) {
  cn_match new = NULL;
  return new;
}

cn_match match_add(cn_match match, card c) {
  if(match == NULL){
    match = malloc(sizeof(struct _s_match));
    match->card = c;
    match->next = NULL;
  }else{
    cn_match temp = match;
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next = malloc(sizeof(struct _s_match));
    temp->next->card = c;
    temp->next->next = NULL;
  }
  return match;
}

unsigned int match_size(cn_match match) {
  assert(match != NULL);
  unsigned int i = 0u;
  cn_match temp = match;
  while(temp != NULL){
    i++;
    temp = temp->next;
  }
  return i;
}

unsigned int match_length(cn_match match) {
  assert(match != NULL);
  unsigned int i = 0u;
  if(is_match_correct(match)){
    i = match_size(match)/2;
  }
  return i;
}

bool is_match_correct(cn_match match) {
  assert(match != NULL);
  bool res = true;
  if(card_player(match->card) != 1){
    res = false;
  }else{
    if(match_size(match) % 2 != 0){
      res = false;
    }else{
      cn_match temp = match;
      while(temp->next != NULL){
        if((card_player(temp->card) == 1 && card_player(temp->next->card) != 2) || (card_player(temp->card) == 2 && card_player(temp->next->card) != 1)){
          res = false;
        }
        temp = temp->next;
      }
    }
  }
  return res;
}

unsigned int winner_total_points(cn_match match) {
  assert(match != NULL);
  unsigned int res = 0u;
  if(is_match_correct(match)){
    unsigned int p1 = 0u;
    unsigned int p2 = 0u;
    cn_match temp = match;
    p1 += card_pair_points(temp->card, temp->next->card, 1);
    p2 += card_pair_points(temp->card, temp->next->card, 2);
    while(temp->next->next != NULL){
      temp = temp->next->next;
      p1 += card_pair_points(temp->card, temp->next->card, 1);
      p2 += card_pair_points(temp->card, temp->next->card, 2);
    }
    if(p1 >= p2){
      res = p1;
    }else{
      res = p2;
    }
  }
  return res;
}

card * match_to_array(cn_match match) {
  assert(match != NULL);
  card *array = calloc(match_size(match), sizeof(card));
  cn_match temp = match;
  for(unsigned int i = 0u; i < match_size(match); i++){
    array[i] = temp->card;
    temp = temp->next;
  }
  assert(array != NULL);
  return array;
}

void match_dump(cn_match match) {
  card *array = match_to_array(match);
  for (unsigned int i=0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
  free(array);
}

cn_match match_destroy(cn_match match) {
  assert(match != NULL);
  cn_match killme;
  while(match != NULL){
    killme = match;
    match = match->next;
    killme->card = card_destroy(killme->card);
    free(killme);
  }
  return match;
}
