#include <stdlib.h>
#include<stdio.h>
#include "searchMouv.h"
#include "../engine/game_types.h"
#include "../tad/linklst.h"

 List deplacement(board plateau, unitsArray tab_unite, int uniteID)
{
    List moving=createEmptyList();
    int x1 = tab_unite->units[uniteID].x;
    int y1 = tab_unite->units[uniteID].y;
    result Dep;

    if((x1+1)<HEIGHT && plateau[x1+1][y1]==0)
    {
        Dep=malloc(sizeof(struct data_mouv));

        Dep->studied_unit=uniteID;
        Dep->type_mouve=depl;
        Dep->deplacement=south;
        Dep->targetId=-1;

        moving=add(Dep,moving);
    }
    if((x1-1)>=0 && plateau[x1-1][y1]==0)
    {
        Dep=malloc(sizeof(struct data_mouv));

        Dep->studied_unit=uniteID;
        Dep->type_mouve=depl;
        Dep->deplacement=north;
        Dep->targetId=-1;

        moving=add(Dep,moving);
    }
    if((y1+1)<WIDTH && plateau[x1][y1+1]==0)
    {
        Dep=malloc(sizeof(struct data_mouv));

        Dep->studied_unit=uniteID;
        Dep->type_mouve=depl;
        Dep->deplacement=east;
        Dep->targetId=-1;

        moving=add(Dep,moving);
    }
    if((y1-1)>=0 && plateau[x1][y1-1]==0)
    {
        Dep=malloc(sizeof(struct data_mouv));

        Dep->studied_unit=uniteID;
        Dep->type_mouve=depl;
        Dep->deplacement=west;
        Dep->targetId=-1;

        moving=add(Dep,moving);
    }

    return moving;
}

List tir_all(board plateau, unitsArray tab_unite, int uniteID)
{
    List shoot=createEmptyList();
    result shooting;

    int dx,dy,i,xinc,yinc,cumul,x,y,compt,touche;
    int xi = tab_unite->units[uniteID].x;
    int yi = tab_unite->units[uniteID].y;
    int xtmp, ytmp;
    int j;
    int target;

    for(j=1;j<=MAX_UNITS;j++)
    {
        if(tab_unite->units[j].owner!=tab_unite->units[uniteID].owner)
        {
            touche=0;
            compt=0;
            x = xi;
            y = yi;
            xtmp=tab_unite->units[j].x;
            ytmp=tab_unite->units[j].y;
            dx = xtmp - xi ;
            dy = ytmp - yi ;
            xinc = ( dx > 0 ) ? 1 : -1 ;
            yinc = ( dy > 0 ) ? 1 : -1 ;
            dx = abs(dx) ;
            dy = abs(dy) ;
            target=j;
            if ( dx > dy ) 
            {
                cumul = dx / 2 ;
                for (i=1;i<=dx;i++) 
                {
                    x += xinc ;
                    cumul += dy ;
                    if (cumul>=dx) 
                    {
                        cumul -= dx ;
                        y += yinc ; 
                    }
                    if(plateau[x][y]==-1 && touche==0)
                    {
                        touche = 1;
                    }
                    else if(plateau[x][y]>=1 && plateau[x][y]<=MAX_UNITS && touche==0)
                    {
                        target=plateau[x][y];
                        if(target==j && tab_unite->units[target].owner!=tab_unite->units[uniteID].owner) touche=2;
                        else touche = 3;
                    }
                    compt++;
                } 
            }
            else {
                cumul = dy / 2 ;
                for (i=1;i<=dy;i++) 
                {
                    y += yinc ;
                    cumul += dx ;
                    if (cumul>=dy)
                    {
                        cumul -= dy ;
                        x += xinc ; 
                    }
                    if(plateau[x][y]==-1 && touche==0)
                    {
                        touche = 1;
                    }
                    else if(plateau[x][y]>=1 && plateau[x][y]<=MAX_UNITS && touche==0)
                    {
                        target=plateau[x][y];
                        if(target==j && tab_unite->units[target].owner!=tab_unite->units[uniteID].owner) touche=2;
                        else touche = 3;
                    }
                    compt++;
                } 
            }
            if((touche==0 || touche==2) && compt<=MAX_DAMAGE)
            {
                shooting=malloc(sizeof(struct data_mouv));

                shooting->studied_unit=uniteID;
                shooting->type_mouve=tir;
                shooting->deplacement=-1;
                shooting->targetId=target;

                shoot=add(shooting,shoot);
            }
        }
    }

    return shoot;
}


 List conversion(board plateau, unitsArray tab_unite, int uniteID)
{
    List convert=createEmptyList();

    int x1 = tab_unite->units[uniteID].x;
    int y1 = tab_unite->units[uniteID].y;
    result Co;

    if((x1+1)<HEIGHT && plateau[x1+1][y1]>0 && (tab_unite->units[plateau[x1+1][y1]].owner!=tab_unite->units[uniteID].owner))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId=plateau[x1+1][y1];

        convert=add(Co,convert);
    }
    if((x1-1)>=0 && plateau[x1-1][y1]>0 && (tab_unite->units[plateau[x1-1][y1]].owner!=tab_unite->units[uniteID].owner))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId=plateau[x1-1][y1];

        convert=add(Co,convert);
    }
    if((y1+1)<WIDTH && plateau[x1][y1+1]>0 && (tab_unite->units[plateau[x1][y1+1]].owner!=tab_unite->units[uniteID].owner))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId=plateau[x1][y1+1];

        convert=add(Co,convert);
    }
    if((y1-1)>=0 && plateau[x1][y1-1]>0 && (tab_unite->units[plateau[x1][y1-1]].owner!=tab_unite->units[uniteID].owner))
    {
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId=plateau[x1][y1-1];

        convert=add(Co,convert);
    }

    return convert;
}

 List concatenation(List a, List b)
{
    if(isEmptyList(a)) return b;
    else if(isEmptyList(b)) return a;
    else
    {
        a.last->next=b.first;
        a.last=b.last;
        return a;
    }
}

 List rechercheMouvement(board plateau, unitsArray tab_unite, int uniteID)
{
    if(tab_unite->units[uniteID].unit_type==cultLeader) 
    return concatenation(deplacement(plateau,tab_unite,uniteID),conversion(plateau,tab_unite,uniteID));
    else
    return concatenation(deplacement(plateau,tab_unite,uniteID),tir_all(plateau,tab_unite,uniteID));
}

List all_mvt(board plateau, unitsArray tab_unite, enum playerId whoplay)
{
    List ALL=createEmptyList();
    List tmp=createEmptyList();
    int i;

    for(i=1;i<=MAX_UNITS;i=i+1)
    {
        if(tab_unite->units[i].owner==whoplay)
        {
            tmp=rechercheMouvement(plateau,tab_unite,i);
            ALL=concatenation(ALL,tmp);
        }
    }

    return ALL;
}