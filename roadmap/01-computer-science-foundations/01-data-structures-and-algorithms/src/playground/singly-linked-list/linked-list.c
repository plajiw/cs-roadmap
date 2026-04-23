#include "linked-list.h"

void initLinkedList(LinkedList *list)
{
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
}

void emptyLinkedList(LinkedList *list)
{
}

bool isEmpty(LinkedList *list)
{
    return list->size == 0;
}

void pushBegin(LinkedList *list, int item)
{
    Node *newNode = createNode(item, NULL);

    if (newNode == NULL)
    {
        printf("[Erro] - Falha na alocação de memória\n");
        return;
    }

    newNode->reference = list->begin;
    list->begin = newNode;

    if (isEmpty(list))
        list->end = newNode;

    list->size++;
}

void pushEnd(LinkedList *list, int item)
{
    Node *newNode = createNode(item, NULL);

    if (newNode == NULL)
    {
        printf("[Erro] - Falha na alocação de memória\n");
        return;
    }

    if (isEmpty(list))
        list->begin = newNode;
    else
        list->begin->reference = newNode;

    list->end = newNode;
    list->size++;
}

void pushPos(LinkedList *list, int item, int pos)
{
}

void popBegin(LinkedList *list)
{
}

void popEnd(LinkedList *list)
{
}

void popPos(LinkedList *list, int item, int pos)
{
}

void printLinkedList(LinkedList *list)
{
}

void getMinMax(LinkedList *list)
{
}

void findItem(LinkedList *list, int item)
{
}

void changeItem(LinkedList *list, int item, int pos)
{
}

void shortLinkedList(LinkedList *list)
{
}

void concatLinkedList(LinkedList *list1, LinkedList *list2)
{
}

void mergeLinkedList(LinkedList *list1, LinkedList *list2)
{
}
