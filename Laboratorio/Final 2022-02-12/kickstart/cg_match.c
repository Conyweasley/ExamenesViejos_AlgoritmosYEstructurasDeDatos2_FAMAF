#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "cg_match.h"
#include "card.h"


struct _s_match {
  unsigned int size; 
  struct _s_match *next; 
  card car;
};

struct _s_card {
  unsigned int number; 
  char suit; 
  unsigned int player; 
   
};

cg_match match_new(void)
{
    cg_match match = NULL; 
    return match; 
    
}

cg_match match_add(cg_match match, card c) 
{ 
    struct _s_match *new_match = calloc(1,sizeof(struct _s_match)); 
    new_match->size = match != NULL ? match->size + 1 : 1; //si la lista no esta vacia, le sumo 1 al tamaño
    new_match->car = c; 
    new_match->next = match; 
    return new_match; 
}


unsigned int match_size(cg_match match)
{
    assert (match != NULL); 
    return match->size; 
   
}

bool is_match_correct(cg_match match) {
  struct _s_match *aux = match; //auxiliar pointer
  bool res, init_p1, pair, in_row; 
  init_p1 = card_player(match -> car) == 1; //me fijo que la carta sea del player 1
  pair = match_size(match) % 2 == 0; //chequeo que los numeros de las cartas sean pares
  in_row = true; 
  while(aux -> next != NULL && in_row){ //si el siguiente no es nulo y no estan en fila
    in_row = (card_player(aux->car) == 1 && card_player(aux -> next -> car) == 2) ||
            (card_player(aux->car) == 2 && card_player(aux -> next -> car) ==1);
    aux = aux -> next;
  }
  return res = init_p1 && pair && in_row;
}

static int player_score(cg_match match, unsigned int player)
{
  struct _s_match *prev = match;
  struct _s_match *aux = match -> next;
  int res = 0;
  char col_1, col_2;
  if(card_color(prev -> car) == 'R'){
    col_1 = 'R';
    col_2 = 'N';
  }else{
    col_1 = 'N';
    col_2 = 'R';    
  }
  if(player == 1){
    while(aux -> next != NULL){
      if(card_player(aux -> car) == 1){
        res += card_drop_points(prev->car, aux-> car, col_1);
      }
      aux = aux -> next;
      prev = prev -> next;
    }
  }
  else{
    while(aux -> next != NULL){
      if(card_player(aux->car) == 2){
        res += card_drop_points(prev -> car, aux -> car, col_2);
      }
      aux = aux->next;
      prev = prev -> next;
    }
    res += card_drop_points(prev -> car, aux -> car, col_2);
  }
  return res;
}

int match_winner(cg_match match){
  if(!is_match_correct(match)){
    return -1;
  }
  int playerOneScore = player_score(match, 1);
  int playerTwoScore = player_score(match, 2);

  if (playerOneScore == playerTwoScore) {
    return 0;
  }
  return playerOneScore > playerTwoScore ? 1 : 2;
}

 int winner_total_points(cg_match match) {
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

//La función match_to_array() debe devolver un arreglo dinámico con las cartas de la línea de juegoen el orden en que fueron agregadas.
card* match_to_array(cg_match match) {
  assert (match != NULL);
  int p=0 ; 
  cg_match tmp= match; 
  card* array = malloc (match_size(match) * sizeof(card)); 
  while (tmp != NULL) {
    array[p] = tmp->car; 
    tmp = tmp->next; 
    p++;
  }

return array;

}
  




void match_dump(cg_match match) {
  card *array = match_to_array(match);
  for (unsigned int i=0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
  free(array);
  array = NULL;
}

cg_match match_destroy(cg_match match)
{
    cg_match temp = match;
    while (match != NULL){
        temp = match; 
        match = match->next; 
        card_destroy(temp->car);
        free(temp); 
        temp = NULL; 

    }
  return NULL;
}
