#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "card.h"

struct _s_card {
  unsigned int number;
  char suit;
  unsigned int player;
};


#define DIAMANTE  "DIAMANTE"
#define TREBOL    "TREBOL"
#define CORAZON   "CORAZON"
#define PICA      "PICA"

static const char *suit_str(char p) {
    const char *str;
    if (p == 'd') {
        str = DIAMANTE;
    } else if (p=='t') {
        str = TREBOL;
    } else if (p=='c') {
        str = CORAZON;
    } else {
        str = PICA;
    }
    return str;
}

/* Representation invariant */

static bool valid_suit(char p) {
  return p=='d' || p=='t' || p=='c' || p=='p';
}

static bool valid_player(int p) {
  return p==1 || p==2;
}

static bool invrep(card c) {
    bool valid_card=false;
    valid_card = c!=NULL &&
                  1 <= c->number && c->number <= 13 &&
                  valid_suit(c->suit) &&
                  valid_player(c->player);
    return valid_card;
}

/* Public functions */

card card_new(unsigned int num, char suit, unsigned int player) {
  assert(1 <= num && num <= 13 && valid_suit(suit) && valid_player(player));
  struct _s_card *new = malloc(sizeof(struct _s_card));
  new->number = num;
  new->suit = suit;
  new->player = player;
  assert(invrep(new));
  return new;
}

unsigned int card_player(card c) {
  return c->player;
}

unsigned int card_number(card c) {
  return c->number;
}

char card_color(card c) {
  if (c->suit == 'd' || c->suit == 'c') {
    return 'R';
  }
  return 'N';
}

char card_suit(card c) {
  return c->suit;
}

bool card_equal_color(card fst, card snd) {
  return card_color(fst) == card_color(snd);//me devuelve true si son del mismo color
}

bool card_equal_number(card fst, card snd) {
  return card_number(fst) == card_number(snd);
}


int card_drop_points(card fst, card snd, char playerColor) {
  int points = 0;
  if(card_color(snd) == playerColor){  
    points++; 
    if(card_equal_color(fst, snd)){ 
      points = points + 2; 
    }
    if(card_equal_number(fst, snd)){
      points = points + 5; 
      if(card_color(fst) == playerColor){
        points = points + 2; 
      }
    }
  }
  else{
    if(card_equal_number(fst, snd)){
      points = points + 5; 
      if(card_color(fst) != playerColor){
        points = -10; 
      }
    }
  }
  return points;
}
void card_dump(card c) {
  assert(invrep(c));
  printf("(%2d, %-7s, %2d)", c->number, suit_str(c->suit), c->player);
}

card card_destroy(card c) {
  assert (invrep(c));
  free(c);
  c=NULL;
  return NULL;
}
