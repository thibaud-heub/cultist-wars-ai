#ifndef __LINKLST_H__
#define __LINKLST_H__

//-----------------------------------------------
// Constants
//-----------------------------------------------


#define __LINK_SIZE__ sizeof(struct __s_List)


//-----------------------------------------------
// New data type
//-----------------------------------------------

enum mouv{
    depl,
    tir,
    conv
};

enum dep{
    north,
    south,
    east,
    west
};

struct data_mouv{
    int studied_unit;
    enum mouv type_mouve;
    enum dep deplacement;
    int targetId;
};
typedef struct data_mouv* result;

typedef result Data;
typedef char Bool;

typedef struct __s_Maillon {
    Data element;
    struct __s_Maillon *next;
}Maillon;

struct __s_List{
    Maillon * first;
    Maillon * last;
};

typedef struct __s_List List;


//-----------------------------------------------
// Prototypes
//-----------------------------------------------


//----- ADT

List createEmptyList (void);
List add (Data _data, List _list);
List tail (List _list);
List tail_with_free (List _list);
Data head (List _list);
Bool isEmptyList (List _list);

//----- Memory management functions

List copyList (List _list);
void freeLink (Maillon* _link);
void freeList (List _list);
void freeResult(result _result);

//----- Toolbox

void printList(List _list);
void printResult(result Mouv);

#endif