#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linklst.h"


//-----------------------------------------------
// Abstract Data Type functions
//-----------------------------------------------


/**
 * Creates an empty list (pointer to nothing)
 * 
 * @returns The NULL pointer
 */
List createEmptyList (void) {
    List tmp;
    tmp.first=NULL;
    tmp.last=NULL;
    return tmp;
}


/**
 * Checks if a list is the empty list and returns a Bool
 * 1 <-> TRUE | 0 <-> FALSE
 * 
 * @param _list The list (a pointer to a __s_List)
 * @returns A Bool containing the result
 */
Bool isEmptyList (List _list) {
    return (_list.first == NULL) ? 1 : 0;
}


/**
 * Returns the Data contained in the list's head
 * 
 * @param _list The list to process
 * @returns The head Data
 */
Data head (List _list) {
    // Can only return the head of a non-empty list
    assert(!isEmptyList(_list));

    return _list.first->element;
}


/**
 * Returns the tail of the given list
 * 
 * @param _list The list to process
 * @returns The given list without the head
 */
List tail (List _list) {
    // Can only return the tail of a non-empty list
    assert(!isEmptyList(_list));
    List tmp;
    tmp.first= _list.first->next;
    if(tmp.first==NULL) tmp.last=NULL;
    else tmp.last=_list.last;
    return tmp;
}

List tail_with_free (List _list) {
    // Can only return the tail of a non-empty list
    assert(!isEmptyList(_list));
    List tmp;
    tmp.first= _list.first->next;
    if(tmp.first==NULL) tmp.last=NULL;
    else tmp.last=_list.last;
    freeLink(_list.first);
    return tmp;
}

/**
 * Adds an element to the list and return a pointer to the
 * new link (without modifying the old list)
 * 
 * @param _data The data to add to the list
 * @param _list The base list
 * @returns A new list containing the new data
 */
List add (Data _data, List _list) {
    Maillon * new_link = (Maillon *)malloc(__LINK_SIZE__);
    new_link->element = _data;
    new_link->next = _list.first;
    if(isEmptyList(_list))
    {
        _list.last=new_link;
    }
    _list.first=new_link;
    return _list;
}


//-----------------------------------------------
// Memory management functions
//-----------------------------------------------


/**
 * Frees a link of a list
 * 
 * @param _link A pointer to a link (List object)
 */
void freeLink (Maillon* _link) {
    free(_link);
}


/**
 * Frees an entire list
 * 
 * @param _list The list to destroy
 */
void freeList (List* _list) {
    List tmp;
    if (!isEmptyList(*_list)) {
        // Free the end of the list
        tmp=tail(*_list);
        freeList(&tmp);
        // Free the head (only remaining element)
        freeResult(head(*_list));
        freeLink(_list->first);
        _list->first=NULL;
        _list->last=NULL;
    }
}



void freeResult(result _result){
    free(_result);
}

/**
 * Make a copy of a list and returns the pointer
 * 
 * @param _list The list to copy
 * @returns A pointer to the new list
 */
List copyList(List _list) {
    // End condition
    if (isEmptyList(_list)) return createEmptyList();

    return add(head(_list), copyList(tail(_list)));
}


//-----------------------------------------------
// Toolbox
//-----------------------------------------------


/**
 * Prints list to the console
 * 
 * @param _list The list to print
 */
void printList (List _list) {
    Maillon * current_link = _list.first;
    while (current_link!=NULL) {
        //printf("%d\n",current_link->element);
        printResult(current_link->element);
        current_link = current_link->next;
    }
}

void printResult(result Mouv)
{
    printf("Unite etudiee : %d, ", Mouv->studied_unit);
    printf("Type de mouvement : %d, ", Mouv->type_mouve);
    printf("Deplacement possible : %d, ", Mouv->deplacement);
    printf("Cible : %d\n ", Mouv->targetId);
}


/*int main(){
    List test=createEmptyList();
    result res=malloc(sizeof(struct data_mouv));
    res->studied_unit=3;
    res->type_mouve=depl;
    res->deplacement=east;
    res->targetId=-1;
    if(isEmptyList(test)) {
        printf("Vrai\n");
        printList(test);}
    else printf("False\n");
    test=add(res,test);
    if(isEmptyList(test)) printf("Vrai\n");
    else{
        printf("False\n");
        printList(test);
    } 
    return 0;
}*/