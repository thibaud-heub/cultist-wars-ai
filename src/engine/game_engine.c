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
int end_of_game(board plateau, unitsArray nb_unite, int player, int turn);

int action(int player, board plateau, unitsArray nb_unite, int turn)
{
    int choix, target_conv, avanc, x, y, tire, target_tire;
    printf("Tour n°%d : Joueur %d, à vous de jouer.\n", turn, player);
    printf("Vous avez le choix de faire :\n");
    printf("- 0 : Convertir une unité \n");
    printf("- 1 : Faire avancer une unité \n");
    printf("- 2 : Tirer sur une unité \n");
    printf("- 3 : Attendre \n");
    printf("- 4 : Arréter le jeu \n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 0:
        printf("Quelle est l'unité ciblée ? ");
        scanf("%d", &target_conv);
        convert(plateau, nb_unite, player, target_conv);
        turn++;
        break;
    case 1:
        printf("Quelle unité va avancer ? ");
        scanf("%d", &avanc);
        printf("Quelle sont les coordonnées de la case ciblée ? ");
        scanf("%d %d", &x, &y);
        move(plateau, player, nb_unite, avanc, x, y);
        turn++;
        break;
    case 2:
        printf("Quelle unité va tirer ? ");
        scanf("%d", &tire);
        printf("Quelle est l'unité ciblée ? ");
        scanf("%d", &target_tire);
        shoot(plateau, nb_unite, tire, target_tire);
        turn++;
        break;
    case 4:
        exit(EXIT_SUCCESS);
        break;
    default:
        wait();
        turn++;
        break;
    }
    printf("Process...\n");
    sleep(0);
    system("clear");
    print_unitsArray(nb_unite);
    printBoard(plateau);
    return end_of_game(plateau, nb_unite, player, turn);
}
int end_of_game(board plateau, unitsArray nb_unite, int player, int turn) // 0: le jeu n'est pas fini , 1: le jeu est fini
{
    if (nb_unite->numOfUnitsTeam0 == 12 || nb_unite->numOfUnitsTeam1 == 12)
        return 1;
    if (turn < MAX_TURNS) // nombre de tour MAX atteint
    {
        return 0;
    }
    return 1; // Le jeu est fini et renvoie 1
}
int who_wins(unitsArray nb_unite) // renvoie l'Id du joueur qui a gagné
{
    if (nb_unite->numOfUnitsTeam0 > nb_unite->numOfUnitsTeam1)
        return 0;
    else
        return 1;
}
int main(int argc, char const *argv[])
{
    int fin = 0, turn = 0, joueur = 0;
    board plateau;
    unitsArray nb_unite = malloc(sizeof(struct unitsArray_s));
    initGame(plateau, nb_unite);
    print_unitsArray(nb_unite);
    printBoard(plateau);
    while (!fin)
    {
        fin = action(joueur, plateau, nb_unite, turn);
        if (fin == 0)
        {
            joueur++;
            fin = action(joueur, plateau, nb_unite, turn);
            turn++;
            joueur--;
        }
    }
    printf("Le joueur %d gagne.", who_wins(nb_unite));
    return 0;
}
