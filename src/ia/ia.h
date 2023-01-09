#ifndef __IA_H__
#define __IA_H__

#include "game_types.h"

void alpha_beta(board plateau,enum playerID play, int turn);

int evaluate_board(unitsArray Lunit);

#endif
