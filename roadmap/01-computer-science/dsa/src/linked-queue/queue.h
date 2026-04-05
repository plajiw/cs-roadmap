#include <stdlib.h>
#include <stdbool.h>
#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue
{
    struct node *head, *tail;
    int size;
} Queue;

void initQueue(Queue *p);

void destroyQueue(Queue *p);

bool isEmpty(Queue *p);

int indexElement(Queue *p, int item);

int firstElement(Queue *p);

void dequeue(Queue *p);

void eraseQueue(Queue *p);

void enqueue(Queue *p, int item);

void printQueue(Queue *p);

#endif