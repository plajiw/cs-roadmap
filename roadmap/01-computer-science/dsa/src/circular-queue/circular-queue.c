#include "circular-queue.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR_CODE -1

void initCircularQueue(CircularQueue* q, int capacity)
{
    if (capacity <= 0)
        return;

    q->data = malloc(sizeof(int) * capacity);

    if (q->data == NULL)
        return;

    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = capacity;
}

void destroyCircularQueue(CircularQueue* q);

void clearCircularQueue(CircularQueue* q);

bool isEmpty(CircularQueue* q)
{
    return q->size == 0;
}

bool isFull(CircularQueue* q)
{
    return q->size == q->capacity;
}

void enqueue(CircularQueue* q, int item)
{
    if (isFull(q))
    {
        printf("Fila esta cheia");
        return;
    }

    q->rear = (q->front + q->size) % q->capacity;
    q->data[q->rear] = item;
    q->size++;
}

void dequeue(CircularQueue* q)
{
    if (isEmpty(q))
    {
        printf("Fila esta vazia");
        return;
    }

    q->front = (q->front + 1 % q->capacity);
    q->size--;
}

int indexElement(CircularQueue* q, int item)
{
    if (isEmpty(q))
    {
        printf("Fila esta vazia");
        return ERROR_CODE;
    }

    for (int i = 0; i < q->size; i++)
    {
        int pos = (q->front + i) % q->capacity;

        if (q->data[pos] == item)
            return pos;
    }

    return ERROR_CODE;
}

int first(CircularQueue* q)
{
    return q->front;
}

int last(CircularQueue* q)
{
    return q->rear;
}

void printCircularQueue(CircularQueue* q)
{
}