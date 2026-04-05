#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "node.h"

void initQueue(Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

bool isEmpty(Queue *q)
{
    return q->head == NULL && q->tail == NULL ? true : false;
}

void destroyQueue(Queue *q)
{
    eraseQueue(q);
    free(q);
}

int indexElement(Queue *q, int item)
{
    Node *current = q->head;
    int index = 0;

    while (current != NULL)
    {
        if (current->value == item)
            return index;

        current = current->next;
        index++;
    }

    return -1;
}

int firstElement(Queue *q)
{
    if (isEmpty(q))
        return -1;

    return q->head->value;
}

void enqueue(Queue *q, int item)
{
    Node *newNode;
    newNode = createNode(item, NULL);

    if (isEmpty(q))
        q->head = newNode;
    else
        q->tail->next = newNode;

    q->tail = newNode;
    q->size++;
}

void dequeue(Queue *q)
{
    if (isEmpty(q))
        return;

    if (q->head->next == NULL)
    {
        q->tail = NULL;
        q->size = 0;
        free(q->head);
        return;
    }

    Node *aux = q->head->next;
    free(q->head);
    q->head = aux;
    q->size--;
}

void eraseQueue(Queue *q)
{
    while (!isEmpty(q))
        dequeue(q);

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void printQueue(Queue *q)
{
    Node *current = q->head;

    while (current != NULL)
    {
        printf("[%d] ", current->value);
        current = current->next;
    }

    printf("\n");
}