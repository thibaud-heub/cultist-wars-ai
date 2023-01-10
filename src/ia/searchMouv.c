#include <stdlib.h>
#include "searchMouv.h"
#include "../engine/game_types.h"
#include "../tad/queue.h"

Queue deplacement(board plateau, unitsArray tab_unite, int uniteID)
{
    Queue moving=create_empty_queue();

    int x1 = tab_unite->units[uniteID].x;
    int y1 = tab_unite->units[uniteID].y;

    if(plateau[x1][y1+1] == '0')
    {
        result Dep1=malloc(sizeof(struct data_mouv));

        Dep1->studied_unit=uniteID;
        Dep1->type_mouve=move;
        Dep1->deplacement=north;
        Dep1->targetId=-1;

        push_back(Dep1,moving);
    }
    if(plateau[x1][y1-1] == '0')
    {
        result Dep2=malloc(sizeof(struct data_mouv));

        Dep2->studied_unit=uniteID;
        Dep2->type_mouve=move;
        Dep2->deplacement=south;
        Dep2->targetId=-1;

        push_back(Dep2,moving);
    }
    if(plateau[x1+1][y1] == '0')
    {
        result Dep3=malloc(sizeof(struct data_mouv));

        Dep3->studied_unit=uniteID;
        Dep3->type_mouve=move;
        Dep3->deplacement=east;
        Dep3->targetId=-1;

        push_back(Dep3,moving);
    }
    if(plateau[x1-1][y1] == '0')
    {
        result Dep4=malloc(sizeof(struct data_mouv));

        Dep4->studied_unit=uniteID;
        Dep4->type_mouve=move;
        Dep4->deplacement=west;
        Dep4->targetId=-1;

        push_back(Dep2,moving);
    }

    return moving;
}

Queue tir_all(board plateau, unitsArray tab_unite, int uniteID)
{
    Queue shoot=create_empty_queue();

    int dx,dy,i,xinc,yinc,cumul,x,y,compt=0,touche=0;
    int xi = tab_unite->units[uniteID].x;
    int yi = tab_unite->units[uniteID].y;

    return shoot;
}

Queue conversion(board plateau, unitsArray tab_unite, int uniteID)
{
    Queue convert=create_empty_queue();

    return convert;
}

Queue rechercheMouvement(board plateau, unitsArray tab_unite, int uniteID)
{

}
