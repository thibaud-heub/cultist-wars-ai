#include "ia.h"
#include<stdio.h>
#include<stdlib.h>

unitsArray init_units(){
    unitsArray nb_unite=malloc(sizeof(struct unitsArray_s));
    int False=1,a,b;
    nb_unite->numOfUnitsTeam0=MAX_UNITS/2;
    nb_unite->numOfUnitsTeam1=MAX_UNITS/2;
    for(int i=0;i<MAX_UNITS;i++)
    {
        nb_unite->units[i].unitId=i;
        nb_unite->units[i].hp=MAX_HP;
        if(i==MAX_UNITS-2) //Initialisation leader 1
        {
            nb_unite->units[i].owner=first;
            nb_unite->units[i].unit_type=cultLeader;
            nb_unite->units[i].x=3;
            nb_unite->units[i].y=0;
        }
        else if(i==MAX_UNITS-1) //Initialisation leader 2
        {
            nb_unite->units[i].owner=second;
            nb_unite->units[i].unit_type=cultLeader;
            nb_unite->units[i].x=3;
            nb_unite->units[i].y=12;
        }
        else
        {
            nb_unite->units[i].owner=first;
            //nb_unite->units[i].unit_type=0;
            if(i>= (MAX_UNITS/2)-1)
            {
                nb_unite->units[i]=nb_unite->units[i-MAX_UNITS/2];
		        nb_unite->units[i].unitId=i;
                nb_unite->units[i].owner=second;
                nb_unite->units[i].hp=MAX_HP;
                nb_unite->units[i].y=12-nb_unite->units[i].y;
                //plateau[nb_unite->units[i].x][nb_unite->units[i].y]='u';
            }
            else 
            {
                while(False)
                {
                    a=rand() % 7 ;
                    b=1 + rand() % 5;
                    if(False) 
                    {
                        nb_unite->units[i].x=a;
                        nb_unite->units[i].y=b;
                        False = 0;
                    } 
                }
            False = 1;
            } 
        }
    }
    return nb_unite;
}



unitsArray init_unitsdif(){
    unitsArray nb_unite=malloc(sizeof(struct unitsArray_s));
    int False=1,a,b;
    nb_unite->numOfUnitsTeam0=MAX_UNITS/2;
    nb_unite->numOfUnitsTeam1=MAX_UNITS/2;
    for(int i=0;i<MAX_UNITS;i++)
    {
        nb_unite->units[i].unitId=i;
        nb_unite->units[i].hp=MAX_HP-i+10;
        if(i==MAX_UNITS-2) //Initialisation leader 1
        {
            nb_unite->units[i].owner=first;
            nb_unite->units[i].unit_type=cultLeader;
            nb_unite->units[i].x=3;
            nb_unite->units[i].y=0;
        }
        else if(i==MAX_UNITS-1) //Initialisation leader 2
        {
            nb_unite->units[i].owner=second;
            nb_unite->units[i].unit_type=cultLeader;
            nb_unite->units[i].x=3;
            nb_unite->units[i].y=12;
        }
        else
        {
            nb_unite->units[i].owner=first;
            //nb_unite->units[i].unit_type=0;
            if(i>=(MAX_UNITS/2)-1)
            {
                nb_unite->units[i]=nb_unite->units[i-MAX_UNITS/2];
		        nb_unite->units[i].unitId=i;
                nb_unite->units[i].owner=second;
                nb_unite->units[i].hp=MAX_HP-i+10;
                nb_unite->units[i].y=12-nb_unite->units[i].y;
                //plateau[nb_unite->units[i].x][nb_unite->units[i].y]='u';
            }
            else 
            {
                while(False)
                {
                    a=rand() % 7 ;
                    b=1 + rand() % 5;
                    if(False) 
                    {
                        nb_unite->units[i].x=a;
                        nb_unite->units[i].y=b;
                        False = 0;
                    } 
                }
            False = 1;
            } 
        }
    }
    return nb_unite;
}


int main(){
    unitsArray test=init_units();
    printf("Test evaluate board\n");
    int score=evaluate_board(test,second);
    printf("%d\n",score);
    free(test);
    test=init_unitsdif();
    score=evaluate_board(test,second);
    printf("%d\n",score);
    score=evaluate_board(test,first);
    printf("%d\n",score);
}