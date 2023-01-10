#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "../engine/game_types.h"
#include "../tad/queue.h"

Queue deplacement(board plateau, unitsArray tab_unite, int uniteID);
Queue tir_all(board plateau, unitsArray tab_unite, int uniteID);
Queue conversion(board plateau, unitsArray tab_unite, int uniteID);
Queue rechercheMouvement(board plateau, unitsArray tab_unite, int uniteID);

#endif
