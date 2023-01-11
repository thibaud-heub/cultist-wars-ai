#include<stdlib.h>
#include"../tad/linklst.h"
#include "ia.h"

Item init_Item(board plateau,unitsArray Lunit){
    Item init=malloc(sizeof(struct ia_result_z));
    copyBoard(plateau,init->plateau);
    init->Lunit=copyUnistArray(Lunit);
    init->mvt=NULL;
    return init;
}

/*ia_result alpha_beta(Item node,int depth,enum playerId whoplay,enum playerId iaPlayer,int alpha,int beta){
    List child;
    result childStudy, bestChild;
    ia_result solution=malloc(sizeof(struct ia_result_z));
    if(depth==MAX_DEPTH){
        solution->mvt=node->mvt;
        solution->value=evaluate_board(node->Lunit,whoplay);
        return solution;
    }
    else{
        child=all_mvt(node->plateau,node->Lunit,whoplay);
        if(isEmptyList(child)){ 
            solution->mvt=node->mvt;
            solution->value=evaluate_board(node->Lunit,whoplay);
            return solution;
        }
        else{
            solution->mvt=node->mvt;
            solution->value=evaluate_board(node->Lunit,whoplay);
            return solution;
        }
    }
}*/

int evaluate_board(unitsArray Lunit,enum playerId whoplay){
    int score=0,i;
    unit studyUnit;
    for(i=0;i<MAX_UNITS;i++){
        studyUnit=Lunit->units[i];
        if (studyUnit.owner==whoplay){
            if (studyUnit.unit_type==cultLeader) score+=(20*(studyUnit.hp));
            else score+=(studyUnit.hp + 1);
        }
        else{
            if(studyUnit.owner!=neutral){
                if (studyUnit.unit_type==cultLeader) score-=(20*(studyUnit.hp));
                else score-=(studyUnit.hp + 1);
            }
        }
    }
    return score;
}

void copyBoard(board initial,board copy){
    int i,j;
    for (i=0;i<HEIGHT;i++){
        for(j=0;j<WIDTH;j++){
            copy[i][j]=initial[i][j];
        }
    }
}

unitsArray copyUnistArray(unitsArray initial){
    unitsArray copy=malloc(sizeof(struct unitsArray_s));
    int i;
    copy->numOfUnitsTeam0=initial->numOfUnitsTeam0;
    copy->numOfUnitsTeam1=initial->numOfUnitsTeam1;
    for (i=0;i<MAX_UNITS;i++){
        copy->units[i]=initial->units[i];
    }
    return copy;
}