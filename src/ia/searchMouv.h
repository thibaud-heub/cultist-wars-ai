#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "game_types.h"

enum mouv{
    move,
    tir,
    convert
};

enum dep{
    north,
    south,
    east,
    west
};

struct data_mouv{
    int studied_unit;
    enum mouv type_mouve;
    enum dep deplacement;
    int targetId;
};
typedef struct data_mouv* result;

typedef struct maillon_z{
    struct maillon_z* next;
    struct maillon_z* prev;
    result mouvement;
}maillon;

typedef struct liste_z{
    maillon* first;
    maillon* last;
}list;

static list deplacement(board plateau, unitsArray tab_unite, int uniteID);
static list tir(board plateau, unitsArray tab_unite, int uniteID);
static list conversion(board plateau, unitsArray tab_unite, int uniteID);
list rechercheMouvement(board plateau, unitsArray tab_unite, int uniteID);

#endif
