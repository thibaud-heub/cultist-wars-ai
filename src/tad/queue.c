#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linklst.h"
#include "queue.h"

Queue create_empty_queue()
{
    Queue q = malloc(sizeof(struct zqueue));
    q->size=0;
    q->front=NULL;
    q->back=NULL;
    return q;
}

bool is_empty_queue(Queue q)
{
    assert(q!=NULL);
    return(q->size==0);
}

void push_back(Data e, Queue q)
{
    List tmp=add(e,NULL);
    if(q->size==0)
    {
        q->front=tmp;
    }
    else
    {
        q->back->next_link=tmp;
    }
    q->back=tmp;
    q->size=q->size+1;
}

Data pop_front(Queue q)
{
    assert(!is_empty_queue(q));
    Data e=head(q->front);
    List l=q->front;
    q->front=tail(q->front);
    q->size=q->size-1;
    freeLink(l);
    return e;
}

Data top_queue(Queue q)
{
    assert(!is_empty_queue(q));
    return head(q->front);
}

void freeQueue(Queue q)
{
    assert(q!=NULL);
    freeList(q->front);
    freeList(q->back);
    free(q);
}

void printQueue(Queue q)
{
    printList(q->front);
}
