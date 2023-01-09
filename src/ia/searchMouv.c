#include "searchMouv.h"
#include "game_types.h"

static list deplacement(board plateau, unitsArray tab_unite, int uniteID)
{
    list move;

    int x1 = tab_unite->units[uniteID].x;
    int y1 = tab_unite->units[uniteID].y;

    if(plateau[x1][y1+1] == '0')
    {

    }
    if(plateau[x1][y1-1] == '0')
    {

    }
    if(plateau[x1+1][y1] == '0')
    {

    }
    if(plateau[x1-1][y1] == '0')
    {

    }

    return move;
}

static list tir(board plateau, unitsArray tab_unite, int uniteID)
{
    list shoot;

    return shoot;
}

static list conversion(board plateau, unitsArray tab_unite, int uniteID)
{
    list convert;

    return convert;
}

list rechercheMouvement(board plateau, unitsArray tab_unite, int uniteID)
{

}
