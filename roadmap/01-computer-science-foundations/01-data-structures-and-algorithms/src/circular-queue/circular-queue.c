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

void destroyCircularQueue(CircularQueue* q)
{
    if (q->data == NULL)
        return;

    free(q->data);
    q->data = NULL;
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = 0;
}

void clearCircularQueue(CircularQueue* q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

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
        printf("[Erro] - Fila esta cheia\n");
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
        printf("[Erro] - Fila esta vazia\n");
        return;
    }

    q->front = (q->front + 1) % q->capacity;
    q->size--;
}

int indexElement(CircularQueue* q, int item)
{
    if (isEmpty(q))
    {
        printf("[Erro] - Fila esta vazia\n");
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

int front(CircularQueue* q)
{
    if (isEmpty(q))
    {
        printf("[Erro] - Fila esta vazia\n");
        return ERROR_CODE;
    }

    return q->front;
}

int rear(CircularQueue* q)
{
    if (isEmpty(q))
    {
        printf("[Erro] - Fila esta vazia\n");
        return ERROR_CODE;
    }

    return q->rear;
}

int first(CircularQueue *q)
{
    if (isEmpty(q))
    {
        printf("[Erro] - Fila esta vazia\n");
        return ERROR_CODE;
    }

    return q->data[front(q)];
}

int last(CircularQueue *q)
{
    if (isEmpty(q))
    {
        printf("[Erro] - Fila esta vazia\n");
        return ERROR_CODE;
    }
    
    return q->data[rear(q)];
}

void printCircularQueue(CircularQueue* q)
{
    if (isEmpty(q))
    {
        printf("[Erro] - Fila esta vazia\n");
        return;
    }

    printf("[");

    for (int i = 0; i < q->size; i++)
    {
        int pos = (q->front + i) % q->capacity;

        if (i > 0)
            printf(", ");

        printf("%d", q->data[pos]);
    }

    printf("]\n");
}