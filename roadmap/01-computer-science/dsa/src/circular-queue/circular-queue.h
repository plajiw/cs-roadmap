#include <stdbool.h>

#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

typedef struct queue
{
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
} CircularQueue;

void initCircularQueue(CircularQueue* q, int capacity);

void destroyCircularQueue(CircularQueue* q);

void clearCircularQueue(CircularQueue* q);

bool isEmpty(CircularQueue* q);

bool isFull(CircularQueue* q);

void enqueue(CircularQueue* q, int item);

void dequeue(CircularQueue* q);

int indexElement(CircularQueue* q, int item);

int first(CircularQueue* q);

int last(CircularQueue* q);

void printCircularQueue(CircularQueue* q);

#endif