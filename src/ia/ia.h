#ifndef __IA_H__
#define __IA_H__

#define INFINITEP 100000
#define INFINITED -100000
#define MAX_DEPTH 5

#include<stdlib.h>
#include"../engine/game.h"
#include "../engine/game_types.h"
#include"../tad/linklst.h"
#include "searchMouv.h"

struct ia_result_z{
    result mvt;
    int value;
};

typedef struct ia_result_z * ia_result;

struct Item_z{
    board plateau;
    unitsArray Lunit;
    result mvt;
};

typedef struct Item_z * Item;

Item init_Item(board plateau,unitsArray Lunit);

ia_result alpha_beta(Item node,int depth,enum playerId whoplay,enum playerId iaPlayer,int alpha,int beta);

int evaluate_board(unitsArray Lunit,enum playerId whoplay);

void copyBoard(board initial,board copy);

unitsArray copyUnistArray(unitsArray initial);

Item getChildNode(Item initial,result mvt);

void moveNode(Item node);

void freeIaResult(ia_result _iaresult);

void freeUnitsArray(unitsArray _unitsArray);

void freeNode(Item _node);

#endif
