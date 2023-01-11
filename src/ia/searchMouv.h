#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "../engine/game_types.h"
#include "../tad/linklst.h"

List deplacement(board plateau, unitsArray tab_unite, int uniteID);
List tir_all(board plateau, unitsArray tab_unite, int uniteID);
List conversion(board plateau, unitsArray tab_unite, int uniteID);
List concatenation(List a, List b);
List rechercheMouvement(board plateau, unitsArray tab_unite, int uniteID);
List all_mvt(board plateau, unitsArray tab_unite, enum playerId whoplay);

#endif
