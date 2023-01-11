#ifndef _GAME_TYPES_H
#define _GAME_TYPES_H

#define MAX_HP 10
#define MAX_DAMAGE 7
#define HEIGHT 7
#define WIDTH 13
#define MAX_RANGE 6
#define MAX_UNITS 14
#define MAX_TURNS 150
 
enum playerId
{
    first,
    second,
    neutral
};

enum unitType
{
    cultist,
    cultLeader
};

typedef int board[HEIGHT][WIDTH];


typedef struct unit_s
{
    int unitId;
    enum unitType unit_type;
    int hp;
    int x;
    int y;
    enum playerId owner;
} unit;

typedef struct unitsArray_s
{   
    int numOfUnitsTeam0;
    int numOfUnitsTeam1;
    unit units[MAX_UNITS+1]; //permet d'avoir les unités dans l'intervale [1;14] et pas 0 qui ne s'affiche pas
} *unitsArray;

#endif