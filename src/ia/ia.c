#include<stdlib.h>
#include "ia.h"



/*result alpha_beta(board plateau,int depth,unitsArray Lunit,enum playerId whoplay,enum playerId iaPlayer,int alpha,int beta){
    int alpha=INFINITED;
    int beta=INFINITEP;
    list child;
    result childStudy, bestChild;
    child=all_mvt(plateau,Lunit,whoplay);
    if(depth==MAX_DEPTH){
        return evaluate_board(Lunit,whoplay);
    }
    if(){  si child est vide discussion avec Félix !!!!!!!!!!!!!!!
        azert
    }
    else{
        return;
    //}
}*/




int evaluate_board(unitsArray Lunit,enum playerId whoplay){
    int score=0,i;
    unit studyUnit;
    for(i=0;i>=MAX_UNITS;i++){
        studyUnit=Lunit->units[i];
        if (studyUnit.owner==whoplay){
            if (studyUnit.unit_type==cultLeader) score+=20*(studyUnit.hp);
            else score+=(studyUnit.hp + 1);
        }
        else{
            if(studyUnit.owner!=neutral){
                if (studyUnit.unit_type==cultLeader) score-=20*(studyUnit.hp);
                else score-=(studyUnit.hp + 1);
            }
        }
    }
    return score;
}

/*list all_mvt(board plateau,unitsArray Lunit,enum playerId whoplay){
    return rechercheMouvement(plateau,Lunit,1);
}*/