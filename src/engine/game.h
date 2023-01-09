#ifndef _GAME_H
#define _GAME_H

#include "game_types.h" 
 
void initGame(board, unitsArray); //initialize the board, put obstacles and neutral units (symetric)

void printBoard(board plateau); //print the board on terminal

void wait(void);

void print_unitsArray(unitsArray nb_unite); //print the unitsArray

void move(board, int player, unitsArray, int unitId, int x, int y);

void shoot(board plateau, unitsArray nb_unite, int uniteId, int targetId);

void convert(board, unitsArray, int unitId, int targetId);

#endif






















    /*int algo_Bresenham(board board, int x1, int y1, int x2, int y2,tab_shoot tableau_mouv)
{
    int dx,dy,compt=0;
    if((dx=x2-x1)!=0)
    {
        if(dx>0)
        {
            if((dy=y2-y1)!=0)
            {
                if(dy>0)
                {
                    if(dx>=dy)
                    {
                        int e;
                        e=dx;
                        dx=e*2;
                        dy=dy*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((x1=x1+1)==x2) break;
                            if((e=e-dy)<0)
                            {
                                y1++;
                                e=e+dx;
                            }
                        }
                    }
                    else
                    {
                        int e;
                        e=dy;
                        dy=e*2;
                        dx=dx*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((y1++)==y2) break;
                            if((e=e-dx)<0)
                            {
                                x1++;
                                e=e+dy;
                            }
                        }
                    }
                }
                else
                {
                    if(dx>=-dy)
                    {
                        int e;
                        e=dx;
                        dx=e*2;
                        dy=dy*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((x1++)==x2) break;
                            if((e=e+dy)<0)
                            {
                                y1++;
                                e=e+dx;
                            }
                        }
                    }
                    else
                    {
                        int e;
                        e=dy;
                        dy=e*2;
                        dx=dx*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((y1--)==y2) break;
                            if((e=e+dx)>0)
                            {
                                x1++;
                                e=e+dy;
                            }
                        }
                    }
                }
            }
            else
            {
                do
                {
                    tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                    tableau_mouv[compt][1]=y1;
                    compt++;
                } while ((x1++)!=x2);
            }
        }
        else
        {
            if((dy=y2-y1)!=0)
            {
                if(dy>0)
                {
                    if(-dx>=dy)
                    {
                        int e;
                        e=dx;
                        dx=e*2;
                        dy=dy*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((x1--)==x2) break;
                            if((e=e+dy)<0)
                            {
                                y1++;
                                e=e+dx;
                            }
                        }
                    }
                    else
                    {
                        int e;
                        e=dy;
                        dy=e*2;
                        dx=dx*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((y1++)==y2) break;
                            if((e=e+dx)>0)
                            {
                                x1--;
                                e=e+dy;
                            }
                        }
                    }
                }
                else
                {
                    if(dx<=dy)
                    {
                        int e;
                        e=dx;
                        dx=e*2;
                        dy=dy*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((x1--)==x2) break;
                            if((e=e-dy)<0)
                            {
                                y1--;
                                e=e+dx;
                            }
                        }
                    }
                    else
                    {
                        int e;
                        e=dy;
                        dy=e*2;
                        dx=dx*2;
                        while(1)
                        {
                            tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                            tableau_mouv[compt][1]=y1;
                            compt++;
                            if((y1--)==y2) break;
                            if((e=e-dx)>0)
                            {
                                x1--;
                                e=e+dy;
                            }
                        }
                    }
                }
            }
            else
            {
                do
                {
                    tableau_mouv[compt][0]=x1;//board[x1][y1]='T';
                    tableau_mouv[compt][1]=y1;
                    compt++;
                } while ((x1--)!=x2);
            }
        }
        
    }
    else
    {
        if((dy=y2-y1)!=0)
        {
            if(dy>0)
            {
                do
                {
                    tableau_mouv[compt][0]=x1;
                    tableau_mouv[compt][1]=y1;
                    //board[x1][y1]='T';
                    compt++;
                } while ((y1++)!=y2);
            }
            else
            {
                do
                {
                    tableau_mouv[compt][0]=x1;
                    tableau_mouv[compt][1]=y1;
                    //board[x1][y1]='T';
                    compt++;
                } while ((y1--)!=y2);   
            }
        }
    }
     //Pour voir quelles sont les valeurs dans le tableau des coordonnées
    for(int i=0;i<compt;i++)
    {
        printf("%d %d\n",tableau_mouv[i][0],tableau_mouv[i][1]);
    }
    return compt;
}*/