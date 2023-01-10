#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "linklst.h"

struct zqueue{
    int size;
    List first;
    List last;
};
typedef struct zqueue *Queue;

Queue create_empty_queue();
bool is_empty_queue(Queue);
void push_back(Data, Queue);
Data pop_front(Queue);
Data top_queue(Queue);
void freeQueue(Queue);
void printQueue(Queue);

#endif