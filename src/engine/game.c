#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "game.h"

void initGame(board plateau, unitsArray nb_unite)
{
    int compt=0,n,x,False=1,a,b,t,attention = 0;
    //Initialisation du board et des obstacles
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            plateau[i][j]='0';
        }
    }
    while(compt<=8)
    {
        x=rand() % 7 ;
        n=1 + rand() % 5;
        if(plateau[x][n] == '0') 
        {
            plateau[x][n]='X';
            plateau[x][12-n]='X';
            compt++;
        } 
    }
    //Initialisation unitsArray
    nb_unite->numOfUnitsTeam0=0;
    nb_unite->numOfUnitsTeam1=0;
    for(int i=0;i<MAX_UNITS;i++)
    {
        nb_unite->units[i].unitId=i;
        nb_unite->units[i].hp=MAX_HP;
        if(i==MAX_UNITS-2) //Initialisation leader 1
        {
            nb_unite->units[i].owner=0;
            nb_unite->units[i].unit_type=1;
            nb_unite->units[i].x=3;
            nb_unite->units[i].y=0;
            plateau[nb_unite->units[i].x][nb_unite->units[i].y]='1';
        }
        else if(i==MAX_UNITS-1) //Initialisation leader 2
        {
            nb_unite->units[i].owner=1;
            nb_unite->units[i].unit_type=1;
            nb_unite->units[i].x=3;
            nb_unite->units[i].y=12;
            plateau[nb_unite->units[i].x][nb_unite->units[i].y]='2';
        }
        else
        {
            nb_unite->units[i].owner=2;
            //nb_unite->units[i].unit_type=0;
            if(i>= MAX_UNITS/2-1)
            {
                nb_unite->units[i]=nb_unite->units[i-(MAX_UNITS/2-1)];
		        nb_unite->units[i].unitId=i;
                nb_unite->units[i].y=12-nb_unite->units[i].y;
                //plateau[nb_unite->units[i].x][nb_unite->units[i].y]='u';
            }
            else 
            {
                while(False)
                {
                    a=rand() % 7 ;
                    b=1 + rand() % 5;
                    for(t=0;t<=i;t++)
                    {
                        if(nb_unite->units[t].x == a && nb_unite->units[t].y == b && attention == 0 && plateau[a][b] == 'X')
                        {
                            attention = 1;//attention : permet de dire si il y a une unité déja présente
                        }
                    }
                    if(attention == 0) 
                    {
                        nb_unite->units[i].x=a;
                        nb_unite->units[i].y=b;
                        //plateau[a][b]='u'; //commande qui permet de savoir ou sont les unités
                        False = 0;
                    } 
                    attention = 0;
                }
            False = 1;
            } 
        }
    }
}

void printBoard(board plateau)
{
    assert(plateau);
	printf("\n");
    printf("    u unités neutres - 1 et 2 leaders - X obstacles\n");
    for (int j=0; j<WIDTH; j++)
    {
        if(j>=10) printf("  %d",j);
        else printf("   %d",j);
    } 
    printf("\n");
	for (int j=0; j<WIDTH; j++)
    {
        if (j==0) printf("  ___");
        else printf("____");
    } 
    printf("\n");
    for(int i=0;i<HEIGHT;i++)
    {
        printf("%d",i);
        for(int j=0;j<WIDTH;j++)
        {
            if(j%WIDTH == 0) printf("|");
            if(plateau[i][j]=='0') printf("   |");
            else printf(" %c |", plateau[i][j]);
        }
        printf("\n");
        for (int j=0; j<WIDTH; j++)
        {
            if (j==0) printf("  ___");
            else printf("____");
        } 
        printf("\n");
        
    }
    printf("\n");
}


void print_unitsArray(unitsArray nb_unite)
{
    printf("\n");
    for(int i=0;i<MAX_UNITS;i++)
    {
        printf("Unité n°%d, Team: %d, hp:%d, x=%d, y=%d\n",nb_unite->units[i].unitId,nb_unite->units[i].owner,nb_unite->units[i].hp,nb_unite->units[i].x,nb_unite->units[i].y);
    }
}
void shoot(board plateau, unitsArray nb_unite, int uniteId, int targetId)
{
    assert(uniteId != targetId || uniteId >= 13 || targetId >= 13);
    int dx,dy,i,xinc,yinc,cumul,x,y,compt=0,touche=0;
    int xi = nb_unite->units[uniteId].x;
    int yi = nb_unite->units[uniteId].y;
    int xf = nb_unite->units[targetId].x;
    int yf = nb_unite->units[targetId].y;

    x = xi ;
    y = yi ;
    dx = xf - xi ;
    dy = yf - yi ;
    xinc = ( dx > 0 ) ? 1 : -1 ;
    yinc = ( dy > 0 ) ? 1 : -1 ;
    dx = abs(dx) ;
    dy = abs(dy) ;
    if ( dx > dy ) 
    {
        cumul = dx / 2 ;
        for ( i = 1 ; i <= dx ; i++ ) 
        {
            x += xinc ;
            cumul += dy ;
            if ( cumul >= dx ) 
            {
                cumul -= dx ;
                y += yinc ; 
            }
            if(plateau[x][y]=='X')
            {
                printf("Le tir a touché un obstacle.\n");
                touche = 1;
            }
            //plateau[x][y]='T';
            compt++;
        } 
    }
    else {
        cumul = dy / 2 ;
        for ( i = 1 ; i <= dy ; i++ ) 
        {
            y += yinc ;
            cumul += dx ;
            if ( cumul >= dy ) 
            {
                cumul -= dy ;
                x += xinc ; 
            }
            if(plateau[x][y]=='X')
            {
                printf("Le tir a touché un obstacle.\n");
                touche = 1;
            }
            //plateau[x][y]='T';
            compt++;
        } 
    }
    if(touche == 0 && compt<=7 && nb_unite->units[targetId].hp != 0)
    {
        nb_unite->units[targetId].hp = nb_unite->units[targetId].hp-(8-compt);
        if(nb_unite->units[targetId].hp == 0)
        {
            if(nb_unite->units[targetId].owner == 0)
            {
                nb_unite->numOfUnitsTeam0--;
            }
            else nb_unite->numOfUnitsTeam1--;
        }
    }   
}
void move(board plateau, int player, unitsArray nb_unite, int uniteId, int x, int y)
{
    int x1 = nb_unite->units[uniteId].x,y1 = nb_unite->units[uniteId].y;
    int i,end=0;
    if(abs(x1-x)<=1 && abs(y1-y)<=1 && !(abs(x1-x)==abs(y1-y)) && plateau[x][y] == '0' && nb_unite->units[uniteId].owner == player)
    {
        for(i=0;i<=MAX_UNITS;i++)
        {
            if(nb_unite->units[i].x == x && nb_unite->units[i].y == y && end == 0)
            {
                end=1;
            }
        }
        if(end == 1)
        {
            fprintf(stderr,"\nL'unité ne peut pas ce déplacer.\n");
        }
        else
        {
            /*plateau[x1][y1]='0';
            if(uniteId >=12) plateau[x][y]='1';
            else plateau[x][y]='u';*/
            nb_unite->units[uniteId].x = x;
            nb_unite->units[uniteId].y = y;
        }
    }
    else
    {
        fprintf(stderr,"\nL'unité ne peut pas ce déplacer.\n");
    }
}
void convert(board plateau, unitsArray nb_unite, int unitId, int targetId)
{

    int x=nb_unite->units[unitId].x,y=nb_unite->units[unitId].y,x1=nb_unite->units[targetId].x,y1=nb_unite->units[targetId].y;
    if(abs(x1-x)<=1 && abs(y1-y)<=1 && !(abs(x1-x)==abs(y1-y)) && nb_unite->units[targetId].owner != nb_unite->units[unitId].owner)
    {
        if(nb_unite->units[unitId].owner == 0) 
        {
            nb_unite->units[targetId].owner = 0;
            //plateau[x1][y1]='A';
            nb_unite->numOfUnitsTeam0++;
        }
        else 
        {
            nb_unite->units[targetId].owner = 1;
            //plateau[x1][y1]='B';
            nb_unite->numOfUnitsTeam1++;
        }
        //printBoard(plateau);
    }
    else
    {
        printf("\n////////////Le leader ne peut pas convertir.////////////\n");
    }
}

void bresenham_me(board plateau,int x0,int y0,int x1,int y1)
{
    int x=x0,y=y0;
    while(x != x1 && y != y1)
    {
        if(((y1-y0)*x-(x1-x0)*y+x1*y0-x0*y1) == 0) 
        {
            plateau[x][y]='T';
            x++;
        }
        else y++;
        printf("%d,%d\n",x,y);
    }
    plateau[x1][y1]='T';
}
/*int main(){
    board plateau;
    unitsArray nb_unite = malloc(sizeof(struct unitsArray_s));
    Cela permet d'initialiser le tableau des coordonnées (inutile en C++)
    for(int i=0;i<MAX_TURNS;i++)
    {
        tableau_coord[i][0]=0;
        tableau_coord[i][1]=0;
    }
    initGame(plateau,nb_unite);
    //int compt=algo_Bresenham(plateau,0,0,5,8,tableau_coord);
    print_unitsArray(nb_unite);
    shoot(plateau,nb_unite,3,13);
    printBoard(plateau);
    print_unitsArray(nb_unite);
    //move(plateau,nb_unite,6,1,0);
    //convert(plateau,nb_unite,12,0);
    printf("\n");
    return 0;
}*/