#ifndef cg_match_H
#define cg_match_H

#include "card.h"
#include <stdbool.h>

typedef struct _s_match * cg_match;

cg_match match_new(void);
/*
* Creates a new match line, initially the match is empty
*
*/

cg_match match_add(cg_match match, card c);
/*
* Adds a card to the match
*
*/

unsigned int match_size(cg_match match);
/*
* Returns number of cards in the match
*
* PRE: {match --> cg_match}
*   size = match_size(match);
* POS: {size >= 0}
*/

bool is_match_correct(cg_match match);
/*
* Indicates if the match is valid.
*/

int match_winner(cg_match match);
/*
* Returns the player that wins the match ( 1 || 2).
* If the match is a tie returns 0
* If the match is invalid it returns -1
*
* PRE: {match --> cg_match}
*   winner = match_winner(match);
* POS: {winner == -1 || 0 || 1 || 2}
*/


int winner_total_points(cg_match match);
/*
* Return the sum of points for the winning player.
* if the match is a tie, returns 0
* if the match is invalid, returns -1
*
* PRE: {match --> cg_match}
*   points = winner_total_points(match);
* POS: {points >= 0}
*/

card * match_to_array(cg_match match);
/*
* Returns an array in dynamic memory that holds all the cards of the match. The
* caller must free the array when it is no longer needed. The returned
* array holds the internal references of the cards used by the cg_match
* instance (the originals, not copies) so the caller MUST NOT DESTROY THEM,
* only has to free the array.
*
* PRE: {match --> cg_match}
*   array = match_to_array(match);
* POS: {array != NULL}
*
*/

void match_dump(cg_match match);
/*
* Shows the match on the screen
*
*/

cg_match match_destroy(cg_match match);
/*
* Destroy the match, freeing all memory.
*
* PRE: {match --> cg_match}
*   match = match_destroy(match);
* POS: {match == NULL}
*
*/

#endif
