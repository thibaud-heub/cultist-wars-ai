/*
 * ----------------------------------------------
 *                 Game_Engine.c
 * ----------------------------------------------
 * 
 * Moteur du jeu, il fait le lien entre 
 * toutes les fonctions du fichiers game.h
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "game.h"

int action(int player,board plateau,unitsArray nb_unite)
{
    int choix,conv,target_conv,avanc,x,y,tire,target_tire,turn = 0;
    printf("Joueur %d, à vous de jouer.\n",player);
    printf("Vous avez le choix de faire :\n");
    printf("- 0 : Convertir une unité \n");
    printf("- 1 : Faire avancer une unité \n");
    printf("- 2 : Tirer sur une unité \n");
    printf("- 3 : Attendre \n");
    scanf("%d",&choix);
    switch(choix)
    {
        case 0 :
            printf("Quelle unité va convertir ?");
            scanf("%d",&conv);
            printf("Quelle est l'unité ciblée ?");
            scanf("%d",&target_conv);
            convert(plateau,nb_unite,conv,target_conv);
            turn++;
            break;
        case 1:
            printf("Quelle unité va avancer ?");
            scanf("%d",&avanc);
            printf("Quelle sont les coordonnées de la case ciblée(libre) ?");
            scanf("%d %d",&x,&y);
            move(plateau,player,nb_unite,avanc,x,y);
            turn++;
            break;
        case 2:
            printf("Quelle unité va tirer ?");
            scanf("%d",&tire);
            printf("Quelle est l'unité ciblée ?");
            scanf("%d",&target_tire);
            shoot(plateau,nb_unite,tire,target_tire);
            turn++;
            break;
        default:
            wait();
            turn++;
            break;

    }
    sleep(3);
    system("clear");
    print_unitsArray(nb_unite);
    printBoard(plateau);
    end_of_game(plateau,nb_unite,player,turn);
    return choix;
}
int end_of_game(board plateau,unitsArray nb_unite, int player,int turn)
{
    int i,j,nb_j0,nb_j1;
    for(i=1;i<=MAX_UNITS;i++)
    {
        if(nb_unite->units[i].owner != 0)
        {
            return 0;
        }
    }
    if(turn == MAX_TURNS)
    {
        for(j=1;j<=MAX_UNITS;j++)
        {
            if(nb_unite->units[j].owner == 0) nb_j0++;
            else if(nb_unite->units[j].owner == 1) nb_j1++;
        }
        if(nb_j0 > nb_j1 && player == 0) 
        {
            return 1;
        }
        else
        {
            if(nb_j0 < nb_j1 && player == 1) 
            {
                return 1;
            }
            return 0;
        }
    }
    return 1;// Le jeu est fini et renvoie 1
}
int main(int argc, char const *argv[])
{ 
    //int fin = 1;
    board plateau;
    unitsArray nb_unite = malloc(sizeof(struct unitsArray_s));
    initGame(plateau,nb_unite);
    print_unitsArray(nb_unite);
    //printBoard(plateau);
    //convert(plateau,nb_unite,13,4,);
    printBoard(plateau);
    //print_unitsArray(nb_unite);
    /*while(fin)
    {
        action(0,plateau,nb_unite);
        action(1,plateau,nb_unite);
    }*/
    return 0;
}