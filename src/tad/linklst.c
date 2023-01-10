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
    return NULL;
}


/**
 * Checks if a list is the empty list and returns a Bool
 * 1 <-> TRUE | 0 <-> FALSE
 * 
 * @param _list The list (a pointer to a __s_List)
 * @returns A Bool containing the result
 */
Bool isEmptyList (List _list) {
    return (_list == NULL) ? 1 : 0;
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

    return _list->element;
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
    
    return _list->next_link;
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
    List new_link = (List)malloc(__LINK_SIZE__);
    new_link->element = _data;
    new_link->next_link = _list;
    return new_link;
}


//-----------------------------------------------
// Memory management functions
//-----------------------------------------------


/**
 * Frees a link of a list
 * 
 * @param _link A pointer to a link (List object)
 */
void freeLink (List _link) {
    free(_link);
}


/**
 * Frees an entire list
 * 
 * @param _list The list to destroy
 */
void freeList (List _list) {
    if (!isEmptyList(_list)) {
        // Free the end of the list
        freeList(tail(_list));
        // Free the head (only remaining element)
        freeLink(_list);
    }
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
    List current_link = _list;

    printf("[");
    
    while (!isEmptyList(current_link)) {
        printResult(current_link->element);
        current_link = current_link->next_link;

        if (!isEmptyList(current_link)) {
            printf(", ");
        }
    }
    
    printf("]\n");
}

void printResult(result Mouv)
{
    printf("[Unité étudiée : %d, ", Mouv->studied_unit);
    printf("Type de mouvement : %d, ", Mouv->type_mouve);
    printf("Deplacement possible : %d, ", Mouv->deplacement);
    printf("Cible : %d] ", Mouv->targetId);
}