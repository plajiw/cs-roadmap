#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

void initLinkedList(LinkedList *list)
{
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
}

void emptyLinkedList(LinkedList *list)
{
    Node *current = list->begin;

    while (current != NULL)
    {
        Node *next = current->reference;
        free(current);
        current = next;
    }

    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
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

    if (list->size == 0)
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
        list->end->reference = newNode;

    list->end = newNode;
    list->size++;
}

void pushPos(LinkedList *list, int item, int pos)
{
    if (pos <= 0 || isEmpty(list))
    {
        pushBegin(list, item);
        return;
    }

    if (pos >= list->size)
    {
        pushEnd(list, item);
        return;
    }

    Node *current = list->begin;

    for (int i = 0; i < pos - 1; i++)
        current = current->reference;

    Node *newNode = createNode(item, current->reference);

    if (newNode == NULL)
    {
        printf("[Erro] - Falha na alocação de memória\n");
        return;
    }

    current->reference = newNode;
    list->size++;
}

void popBegin(LinkedList *list)
{
    if (isEmpty(list))
        return;

    Node *aux = list->begin;

    if (list->begin->reference == NULL)
    {
        list->begin = NULL;
        list->end = NULL;
    }
    else
    {
        list->begin = list->begin->reference;
    }

    free(aux);
    list->size--;
}

void popEnd(LinkedList *list)
{
    if (isEmpty(list))
        return;

    if (list->size == 1)
    {
        free(list->begin);
        list->begin = NULL;
        list->end = NULL;
        list->size = 0;
        return;
    }

    Node *current = list->begin;

    while (current->reference != list->end)
        current = current->reference;

    free(list->end);
    list->end = current;
    list->end->reference = NULL;
    list->size--;
}

void popPos(LinkedList *list, int item, int pos)
{
    if (isEmpty(list))
        return;

    if (pos <= 0)
    {
        popBegin(list);
        return;
    }

    if (pos >= list->size - 1)
    {
        popEnd(list);
        return;
    }

    Node *current = list->begin;

    for (int i = 0; i < pos - 1; i++)
        current = current->reference;

    Node *aux = current->reference;
    current->reference = aux->reference;
    free(aux);
    list->size--;
}

void printLinkedList(LinkedList *list)
{
    Node *current = list->begin;

    while (current != NULL)
    {
        printf("[%d] ", current->data);
        current = current->reference;
    }

    printf("\n");
}

void getMinMax(LinkedList *list)
{
    if (isEmpty(list))
        return;

    Node *current = list->begin;
    int min = current->data;
    int max = current->data;

    while (current != NULL)
    {
        if (current->data < min)
            min = current->data;
        if (current->data > max)
            max = current->data;

        current = current->reference;
    }

    printf("Min: %d | Max: %d\n", min, max);
}

void findItem(LinkedList *list, int item)
{
    Node *current = list->begin;
    int index = 0;

    while (current != NULL)
    {
        if (current->data == item)
        {
            printf("Item [%d] encontrado na posição %d\n", item, index);
            return;
        }

        current = current->reference;
        index++;
    }

    printf("Item [%d] não encontrado\n", item);
}

void changeItem(LinkedList *list, int item, int pos)
{
    if (isEmpty(list) || pos < 0 || pos >= list->size)
        return;

    Node *current = list->begin;

    for (int i = 0; i < pos; i++)
        current = current->reference;

    current->data = item;
}

// ordenar com bubble sort
void sortLinkedList(LinkedList *list)
{
    if (isEmpty(list) || list->size == 1)
        return;

    bool trocou;
    do {
        trocou = false;
        for (Node *cur = list->begin; cur->reference != NULL; cur = cur->reference) {
            if (cur->data > cur->reference->data) {
                int tmp = cur->data;
                cur->data = cur->reference->data;
                cur->reference->data = tmp;
                trocou = true;
            }
        }
    } while (trocou);
}

void concatLinkedList(LinkedList *list1, LinkedList *list2)
{
    if (isEmpty(list2))
        return;

    if (isEmpty(list1))
    {
        list1->begin = list2->begin;
        list1->end = list2->end;
        list1->size = list2->size;
    }
    else
    {
        list1->end->reference = list2->begin;
        list1->end = list2->end;
        list1->size += list2->size;
    }

    list2->begin = NULL;
    list2->end = NULL;
    list2->size = 0;
}

void mergeLinkedList(LinkedList *list1, LinkedList *list2)
{
    LinkedList merged;
    initLinkedList(&merged);

    Node *a = list1->begin;
    Node *b = list2->begin;

    while (a != NULL && b != NULL)
    {
        if (a->data <= b->data)
        {
            pushEnd(&merged, a->data);
            a = a->reference;
        }
        else
        {
            pushEnd(&merged, b->data);
            b = b->reference;
        }
    }

    while (a != NULL)
    {
        pushEnd(&merged, a->data);
        a = a->reference;
    }

    while (b != NULL)
    {
        pushEnd(&merged, b->data);
        b = b->reference;
    }

    emptyLinkedList(list1);
    emptyLinkedList(list2);

    list1->begin = merged.begin;
    list1->end = merged.end;
    list1->size = merged.size;
}
