#ifndef __IA_H__
#define __IA_H__

#define INFINITEP 100000
#define INFINITED -100000
#define MAX_DEPTH 5

#include "../game_types.h"
#include "searchMouv.h"

struct ia_result_z{
    result mvt;
    int value;
};

typedef struct ia_result_z ia_result;

ia_result alpha_beta(board plateau,int depth,unitsArray Lunit,enum playerId whoplay,enum playerId iaPlayer,int alpha,int beta);

int evaluate_board(unitsArray Lunit,enum playerId whoplay);

#endif
