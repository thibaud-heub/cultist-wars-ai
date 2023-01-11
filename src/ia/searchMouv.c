#include <stdlib.h>
#include "searchMouv.h"
#include "../engine/game_types.h"
#include "../tad/linklst.h"

 List deplacement(board plateau, unitsArray tab_unite, int uniteID)
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

 List tir_all(board plateau, unitsArray tab_unite, int uniteID)
{
    List shoot=createEmptyList();
    result shooting;

    int dx,dy,i,xinc,yinc,cumul,x,y,compt=0,touche=0;
    int xi = tab_unite->units[uniteID].x;
    int yi = tab_unite->units[uniteID].y;
    int j,k;
    char tmp1,tmp2;

    x = xi;
    y = yi;

    if(tab_unite->units[uniteID].owner==first) tmp1='A',tmp2='1';
    else tmp1='B',tmp2='2';

    for(j=0;j<HEIGHT;j++)
    {
        for(k=0;k<WIDTH;k++)
        {
            if(plateau[j][k]!=tmp1 && plateau[j][k]!=tmp2)
            {
                dx = k - xi ;
                dy = j - yi ;
                xinc = ( dx > 0 ) ? 1 : -1 ;
                yinc = ( dy > 0 ) ? 1 : -1 ;
                dx = abs(dx) ;
                dy = abs(dy) ;
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
                        if(plateau[x][y]=='X')
                        {
                            touche = 1;
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
                        if(plateau[x][y]=='X')
                        {
                            touche = 1;
                        }
                        compt++;
                    } 
                }
                if(touche == 0 && compt<=7)
                {
                    shooting=malloc(sizeof(struct data_mouv));

                    shooting->studied_unit=uniteID;
                    shooting->type_mouve=tir;
                    shooting->deplacement=-1;
                    shooting->targetId= 2; /////////////////////////////////// A CHANGER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                    add(shooting,shoot);
                }
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
    char test;

    if (tab_unite->units[uniteID].owner==first) test='B';
    else test='A';

    if((y1+1)<HEIGHT && ((test==plateau[x1][y1+1]) || plateau[x1][y1+1]=='u'))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId= 4;/////////////////////////////////// A CHANGER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        add(Co,convert);
    }
    if((y1-1)>=0 && ((test==plateau[x1][y1-1]) || plateau[x1][y1-1]=='u'))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId= 5;/////////////////////////////////// A CHANGER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        add(Co,convert);
    }
    if((x1+1)<WIDTH && ((test==plateau[x1+1][y1]) || plateau[x1+1][y1]=='u'))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId= 6;/////////////////////////////////// A CHANGER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        add(Co,convert);
    }
    if((x1-1)>=0 && ((test==plateau[x1-1][y1]) || plateau[x1-1][y1]=='u'))
    {   
        Co=malloc(sizeof(struct data_mouv));

        Co->studied_unit=uniteID;
        Co->type_mouve=conv;
        Co->deplacement=-1;
        Co->targetId= 7;/////////////////////////////////// A CHANGER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        add(Co,convert);
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