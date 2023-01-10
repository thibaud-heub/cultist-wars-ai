#include <stdlib.h>
#include "searchMouv.h"
#include "../engine/game_types.h"
#include "../tad/linklst.h"

Static List deplacement(board plateau, unitsArray tab_unite, int uniteID)
{
    List moving=createEmptyList();
    int x1 = tab_unite->units[uniteID].x;
    int y1 = tab_unite->units[uniteID].y;
    result Dep;

    if((y1+1)<HEIGHT && plateau[x1][y1+1]=='0')
    {
        Dep=malloc(sizeof(struct data_mouv));

        Dep->studied_unit=uniteID;
        Dep->type_mouve=depl;
        Dep->deplacement=north;
        Dep->targetId=-1;

        add(Dep,moving);
    }
    if((y1-1)>=0 && plateau[x1][y1-1]=='0')
    {
        Dep=malloc(sizeof(struct data_mouv));

        Dep->studied_unit=uniteID;
        Dep->type_mouve=depl;
        Dep->deplacement=south;
        Dep->targetId=-1;

        add(Dep,moving);
    }
    if((x1+1)<WIDTH && plateau[x1+1][y1]=='0')
    {
        Dep=malloc(sizeof(struct data_mouv));

        Dep->studied_unit=uniteID;
        Dep->type_mouve=depl;
        Dep->deplacement=east;
        Dep->targetId=-1;

        add(Dep,moving);
    }
    if((x1-1)>=0 && plateau[x1-1][y1]=='0')
    {
        Dep=malloc(sizeof(struct data_mouv));

        Dep->studied_unit=uniteID;
        Dep->type_mouve=depl;
        Dep->deplacement=west;
        Dep->targetId=-1;

        add(Dep,moving);
    }

    return moving;
}

Static List tir_all(board plateau, unitsArray tab_unite, int uniteID)
{
    List shoot=create_empty_List();

    int dx,dy,i,xinc,yinc,cumul,x,y,compt=0,touche=0;
    int xi = tab_unite->units[uniteID].x;
    int yi = tab_unite->units[uniteID].y;

    return shoot;
}

Static List conversion(board plateau, unitsArray tab_unite, int uniteID)
{
    List convert=create_empty_List();

    int x1 = tab_unite->units[uniteID].x;
    int y1 = tab_unite->units[uniteID].y;
    int i;
    result Co;
    char test;

    if (tab_unite->units[uniteID].owner==first) test='B';
    else test='A';

    if((y1+1)<HEIGHT && ((test==plateau[x1][y1+1]) || plateau[x1][y1+1]=='u'))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId= ;

        add(Co,convert);
    }
    if((y1-1)>=0 && ((test==plateau[x1][y1-1]) || plateau[x1][y1-1]=='u'))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId= ;

        add(Co,convert);
    }
    if((x1+1)<WIDTH && ((test==plateau[x1+1][y1]) || plateau[x1+1][y1]=='u'))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId= ;

        add(Co,convert);
    }
    if((x1-1)>=0 && ((test==plateau[x1-1][y1]) || plateau[x1-1][y1]=='u'))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId= ;

        add(Co,convert);
    }

    return convert;
}

Static List concatenation(List a, List b)
{
    if(is_empty_List(a)) return b;
    else if(is_empty_List(b)) return a;
    else
    {
        a.last->next=b.front;
        a.last=b.last;
        return a;
    }
}

Static List rechercheMouvement(board plateau, unitsArray tab_unite, int uniteID)
{
    if(tab_unite->units[uniteID].unit_type==cultLeader) 
    return concatenation(deplacement(plateau,tab_unite,uniteID),conversion(plateau,tab_unite,uniteID));
    else
    return concatenation(deplacement(plateau,tab_unite,uniteID),tir_all(plateau,tab_unite,uniteID));
}

List all_mvt(board plateau, unitsArray tab_unite, enum playerId whoplay)
{
    List ALL=create_empty_List();
    List tmp=create_empty_List();
    int i;

    for(i=0;i<MAX_UNITS;i=i+1)
    {
        if(tab_unite->units[i].owner==whoplay)
        {
            tmp=rechercheMouvement(plateau,tab_unite,i);
            ALL=concatenation(ALL,tmp);
        }
    }

    return ALL;
}