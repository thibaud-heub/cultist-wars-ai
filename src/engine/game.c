#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "game.h"

void initGame(board plateau, unitsArray nb_unite)
{
    int compt = 0, n, x, False = 1, a, b, t, attention = 0;
    srand(time(NULL)); //permet de générer des seed aléatoire pour la fonction rand()
    // Initialisation du board et des obstacles
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            plateau[i][j] = 0;
        }
    }
    while (compt <= 8)
    {
        x = rand() % 7;
        n = 1 + rand() % 5;
        if (plateau[x][n] == 0)
        {
            plateau[x][n] = -1;
            plateau[x][12 - n] = -1;
            compt++;
        }
    }
    // Initialisation unitsArray
    nb_unite->numOfUnitsTeam0 = 1; // le leader est compté dans le total des unités
    nb_unite->numOfUnitsTeam1 = 1;
    for (int i = 1; i <= MAX_UNITS; i++)
    {
        nb_unite->units[i].unitId = i;
        nb_unite->units[i].hp = MAX_HP;
        if (i == MAX_UNITS - 1) // Initialisation leader 1
        {
            nb_unite->units[i].owner = first;
            nb_unite->units[i].unit_type = second;
            nb_unite->units[i].x = 3;
            nb_unite->units[i].y = 0;
            plateau[nb_unite->units[i].x][nb_unite->units[i].y] = 13;
        }
        else if (i == MAX_UNITS ) // Initialisation leader 2
        {
            nb_unite->units[i].owner = second;
            nb_unite->units[i].unit_type = 1;
            nb_unite->units[i].x = 3;
            nb_unite->units[i].y = 12;
            plateau[nb_unite->units[i].x][nb_unite->units[i].y] = 14;
        }
        else
        {
            nb_unite->units[i].owner = neutral;
            // nb_unite->units[i].unit_type=0;
            if (i >= MAX_UNITS / 2 )
            {
                nb_unite->units[i] = nb_unite->units[i - (MAX_UNITS / 2 - 1)];
                nb_unite->units[i].unitId = i;
                nb_unite->units[i].y = 12 - nb_unite->units[i].y;
                plateau[nb_unite->units[i].x][nb_unite->units[i].y] = i;
            }
            else
            {
                while (False)
                {
                    a = rand() % 7;
                    b = 1 + rand() % 5;
                    for (t = 0; t <= i; t++)
                    {
                        if ((nb_unite->units[t].x == a && nb_unite->units[t].y == b && attention == 0) || plateau[a][b] == -1)
                        {
                            attention = 1; // variable attention : permet de dire si il y a une unité déja présente
                        }
                    }
                    if (attention == 0)
                    {
                        nb_unite->units[i].x = a;
                        nb_unite->units[i].y = b;
                        plateau[a][b] = i; // commande qui permet de savoir ou sont les unités
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
    for (int j = 0; j < WIDTH; j++)
    {
        if (j >= 10)
            printf("  %d", j);
        else
            printf("   %d", j);
    }
    printf("\n");
    for (int j = 0; j < WIDTH; j++)
    {
        if (j == 0)
            printf("  ___");
        else
            printf("____");
    }
    printf("\n");
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("%d", i);
        for (int j = 0; j < WIDTH; j++)
        {
            if (j % WIDTH == 0)
                printf("|");
            if(plateau[i][j] == -1)
                printf(" X |");
            else if(plateau[i][j] == 0)
                printf("   |");
            else if(plateau[i][j] >= 10)
                printf(" %d|",plateau[i][j]);
            else
                printf(" %d |",plateau[i][j]);
        }
        printf("\n");
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                printf("  ___");
            else
                printf("____");
        }
        printf("\n");
    }
    printf("\n");
}

void print_unitsArray(unitsArray nb_unite)
{
    printf("\n");
    printf("Nombre unités Team 0 : %d\n",nb_unite->numOfUnitsTeam0);
    printf("Nombre unités Team 1 : %d\n\n",nb_unite->numOfUnitsTeam1);
    for (int i = 1; i <= MAX_UNITS; i++)
    {
        printf("Unité n°%d, Team: %d, hp:%d, x=%d, y=%d\n", nb_unite->units[i].unitId, nb_unite->units[i].owner, nb_unite->units[i].hp, nb_unite->units[i].x, nb_unite->units[i].y);
    }
}
void shoot(board plateau, unitsArray nb_unite, int uniteId, int targetId)
{
    int dx, dy, i, xinc, yinc, cumul, x, y, compt = 0, touche = 0,compt_touch2 = 0; // touche : 0 rien n'a été touché entre la source et la cible, 1 un obstacle a été touché, 2 un ennemis a été touché
    int xi = nb_unite->units[uniteId].x;
    int yi = nb_unite->units[uniteId].y;
    int xf = nb_unite->units[targetId].x;
    int yf = nb_unite->units[targetId].y;

    if(uniteId != targetId && uniteId <= MAX_UNITS && uniteId >= 1 && targetId <= MAX_UNITS && targetId >=1 )
    {
        x = xi;
        y = yi;
        dx = xf - xi;
        dy = yf - yi;
        xinc = (dx > 0) ? 1 : -1;
        yinc = (dy > 0) ? 1 : -1;
        dx = abs(dx);
        dy = abs(dy);
        if (dx > dy)
        {
            cumul = dx / 2;
            for (i = 1; i <= dx && touche == 0; i++)
            {
                x += xinc;
                cumul += dy;
                if (cumul >= dx)
                {
                    cumul -= dx;
                    y += yinc;
                }
                if (plateau[x][y] == -1 && touche == 0)
                {
                    printf("Le tir a touché un obstacle.\n");
                    touche = 1;
                }
                else if(plateau[x][y] >= 1 && plateau[x][y] <= MAX_UNITS && touche == 0)
                {
                    touche = 2;
                    targetId = plateau[x][y];
                }
                compt++;
            }
        }
        else
        {
            cumul = dy / 2;
            for (i = 1; i <= dy && touche == 0; i++)
            {
                y += yinc;
                cumul += dx;
                if (cumul >= dy)
                {
                    cumul -= dy;
                    x += xinc;
                }
                if (plateau[x][y] == -1 && touche == 0)
                {
                    printf("Le tir a touché un obstacle.\n");
                    touche = 1;
                }
                else if(plateau[x][y] >= 1 && plateau[x][y] <= MAX_UNITS && touche == 0)
                {
                    touche = 2;
                    targetId = plateau[x][y];
                    compt_touch2 = compt+1;
                }
                compt++;
            }
        }
        if ((touche == 0 || touche == 2) && compt <= MAX_DAMAGE && nb_unite->units[targetId].hp != 0)
        {
            if(touche == 2)
                nb_unite->units[targetId].hp = nb_unite->units[targetId].hp - (8 - compt_touch2);
            else 
                nb_unite->units[targetId].hp = nb_unite->units[targetId].hp - (8 - compt);
            if (nb_unite->units[targetId].hp <= 0)
            {
                plateau[nb_unite->units[targetId].x][nb_unite->units[targetId].y] = 0;
                if (nb_unite->units[targetId].owner == first)
                {
                    nb_unite->numOfUnitsTeam0--;
                }
                else
                    nb_unite->numOfUnitsTeam1--;
            }
        }
    }
    else
    {
        if (nb_unite->units[uniteId].owner == first)
            nb_unite->numOfUnitsTeam0 = 0;
        else
            nb_unite->numOfUnitsTeam1 = 0;
    }
}
void move(board plateau, int player, unitsArray nb_unite, int uniteId, int x, int y)
{
    int x1 = nb_unite->units[uniteId].x, y1 = nb_unite->units[uniteId].y;
    if (abs(x1 - x) <= 1 && abs(y1 - y) <= 1 && !(abs(x1 - x) == abs(y1 - y)) && plateau[x][y] == 0 && nb_unite->units[uniteId].owner == player && x>=0 && x< HEIGHT && y>=0 && y< WIDTH && uniteId >0 && uniteId <= MAX_UNITS)
    {
        if (plateau[x][y] != 0)
        {
            fprintf(stderr, "\nL'unité ne peut pas ce déplacer.\n");
            if (player == first)
                nb_unite->numOfUnitsTeam0 = 0;
            else
                nb_unite->numOfUnitsTeam1 = 0;
        }
        else
        {
            plateau[x1][y1] = 0;
            if (uniteId == 13)
            {
                plateau[x][y] = 13;
            }
            else if (uniteId == 14)
            {
                plateau[x][y] = 14;
            }
            else
            {
                plateau[x][y] = uniteId;
            }
            nb_unite->units[uniteId].x = x;
            nb_unite->units[uniteId].y = y;
        }
    }
    else
    {
        fprintf(stderr, "\nL'unité ne peut pas ce déplacer.\n");
        if (player == first)
            nb_unite->numOfUnitsTeam0 = 0;
        else
            nb_unite->numOfUnitsTeam1 = 0;
    }
}
void convert(board plateau, unitsArray nb_unite, int player, int targetId)
{

    int x,y;
    int x1 = nb_unite->units[targetId].x, y1 = nb_unite->units[targetId].y;
    if(player == first)
    {
        x = nb_unite->units[13].x;
        y = nb_unite->units[13].y;
    }
    else
    {
        x = nb_unite->units[14].x;
        y = nb_unite->units[14].y;
    }
    if (abs(x1 - x) <= 1 && abs(y1 - y) <= 1 && !(abs(x1 - x) == abs(y1 - y)) && nb_unite->units[targetId].owner != player && targetId != 13 && targetId != 14)
    {
        if (player == first)
        {
            nb_unite->units[targetId].owner = first;
            //plateau[x1][y1] = 'A';
            nb_unite->numOfUnitsTeam0++;
        }
        else
        {
            nb_unite->units[targetId].owner = second;
            //plateau[x1][y1] = 'B';
            nb_unite->numOfUnitsTeam1++;
        }
    }
    else
    {
        printf("\n////////////Le leader ne peut pas convertir.////////////\n");
        if (player == first)
            nb_unite->numOfUnitsTeam0 = 0;
        else
            nb_unite->numOfUnitsTeam1 = 0;
    }
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