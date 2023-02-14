#include "ia.h"
#include <stdio.h>


void make_move_IA(board plateau,unitsArray Lunit,enum playerId iaPlayer){
    Item node=init_Item(plateau,Lunit);
    ia_result move=alpha_beta(node,0,iaPlayer,iaPlayer,INFINITED,INFINITEP);
    freeNode(node);
    if (move->mvt->type_mouve==depl) moveNodeFinish(plateau,Lunit,move->mvt);
    else if (move->mvt->type_mouve==tir) shoot(plateau,Lunit,move->mvt->studied_unit,move->mvt->targetId);
    else if (move->mvt->type_mouve==conv) convert(plateau,Lunit,Lunit->units[move->mvt->studied_unit].owner,move->mvt->targetId);
    freeIaResult(move);
}

Item init_Item(board plateau,unitsArray Lunit){
    Item init=malloc(sizeof(struct Item_z));
    copyBoard(plateau,init->plateau);
    init->Lunit=copyUnistArray(Lunit);
    init->mvt=NULL;
    return init;
}

ia_result alpha_beta(Item node,int depth,enum playerId whoplay,enum playerId iaPlayer,int alpha,int beta){
    List Lchild;
    Item studynode;
    result childStudy;
    ia_result bestchild,childresult;
    if(depth==MAX_DEPTH){
        bestchild=malloc(sizeof(struct ia_result_z));
        bestchild->mvt=node->mvt;
        bestchild->value=evaluate_board(node->Lunit,iaPlayer);
        return bestchild;
    }
    else{
        Lchild=all_mvt(node->plateau,node->Lunit,whoplay);
        if(isEmptyList(Lchild)){ 
            bestchild=malloc(sizeof(struct ia_result_z));
            bestchild->mvt=node->mvt;
            bestchild->value=evaluate_board(node->Lunit,iaPlayer);
            return bestchild;
        }
        else{
            childStudy=head(Lchild);
            studynode=getChildNode(node,childStudy);
            bestchild=alpha_beta(studynode,depth+1,(whoplay+1)%2,iaPlayer,alpha,beta);
            freeNode(studynode);
            Lchild=tail_with_free(Lchild);
            if(whoplay==iaPlayer){
                if (alpha < bestchild->value) alpha=bestchild->value;
                while (!(isEmptyList(Lchild)) && (alpha<beta)){
                    childStudy=head(Lchild);
                    studynode=getChildNode(node,childStudy);
                    childresult=alpha_beta(studynode,depth+1,(whoplay+1)%2,iaPlayer,alpha,beta);
                    freeNode(studynode);
                    if (childresult->value > bestchild->value){
                        freeIaResult(bestchild);
                        bestchild=childresult;
                        if (alpha < bestchild->value) alpha=bestchild->value;
                    }
                    else freeIaResult(childresult);
                    Lchild=tail_with_free(Lchild);
                }
                freeList(&Lchild);
                freeResult(bestchild->mvt);
                if (depth!=0) bestchild->mvt=node->mvt;
                return bestchild;
            }
            else {
                if (beta > bestchild->value) beta=bestchild->value;
                while (!(isEmptyList(Lchild)) && (alpha<beta)){
                    childStudy=head(Lchild);
                    studynode=getChildNode(node,childStudy);
                    childresult=alpha_beta(studynode,depth+1,(whoplay+1)%2,iaPlayer,alpha,beta);
                    freeNode(studynode);
                    if (childresult->value < bestchild->value){
                        freeIaResult(bestchild);
                        bestchild=childresult;
                        if (beta > bestchild->value) beta=bestchild->value;
                    }
                    else freeIaResult(childresult);
                    Lchild=tail(Lchild);
                }
                freeList(&Lchild);
                freeResult(bestchild->mvt);
                if (depth!=0) bestchild->mvt=node->mvt;
                return bestchild;
            }
        }
    }
}

int evaluate_board(unitsArray Lunit,enum playerId whoplay){
    int score=0,i;
    unit studyUnit;
    for(i=1;i<=MAX_UNITS;i++){
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


//--- Make child node

Item getChildNode(Item initial,result mvt){
    Item copy=malloc(sizeof(struct Item_z));
    copyBoard(initial->plateau,copy->plateau);
    copy->Lunit=copyUnistArray(initial->Lunit);
    copy->mvt=mvt;
    if (mvt->type_mouve==depl) moveNode(copy);
    else if (mvt->type_mouve==tir) shoot(copy->plateau,copy->Lunit,mvt->studied_unit,mvt->targetId);
    else if (mvt->type_mouve==conv) convert(copy->plateau,copy->Lunit,copy->Lunit->units[mvt->studied_unit].owner,mvt->targetId);
    return copy;
}

void moveNode(Item node){
    int x=node->Lunit->units[node->mvt->studied_unit].x,y=node->Lunit->units[node->mvt->studied_unit].y;
    if (node->mvt->deplacement==north) x-=1;
    else if (node->mvt->deplacement==south) x+=1;
    else if (node->mvt->deplacement==east) y+=1;
    else y-=1;
    move(node->plateau,node->Lunit->units[node->mvt->studied_unit].owner,node->Lunit,node->mvt->studied_unit,x,y);
}

void moveNodeFinish(board plateau,unitsArray Lunit,result mvt){
    int x=Lunit->units[mvt->studied_unit].x,y=Lunit->units[mvt->studied_unit].y;
    if (mvt->deplacement==north) x-=1;
    else if (mvt->deplacement==south) x+=1;
    else if (mvt->deplacement==east) y+=1;
    else y-=1;
    move(plateau,Lunit->units[mvt->studied_unit].owner,Lunit,mvt->studied_unit,x,y);
}

//---- Data Management

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
    for (i=1;i<=MAX_UNITS;i++){
        copy->units[i]=initial->units[i];
    }
    return copy;
}

void freeIaResult(ia_result _iaresult){
    freeResult(_iaresult->mvt);
    free(_iaresult);
}

void freeUnitsArray(unitsArray _unitsArray){
    free(_unitsArray);
}

void freeNode(Item _node){
    freeUnitsArray(_node->Lunit);
    free(_node);
}