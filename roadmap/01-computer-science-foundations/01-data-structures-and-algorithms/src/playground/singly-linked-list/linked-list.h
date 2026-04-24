#include <stdint.h>
#include <stdbool.h>
#include <node.h>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct linkedList
{
    Node *begin;
    Node *end;
    int size;
} LinkedList;

void initLinkedList(LinkedList *list);

void emptyLinkedList(LinkedList *list);

bool isEmpty(LinkedList *list);

void pushBegin(LinkedList *list, int item);

void pushEnd(LinkedList *list, int item);

void pushPos(LinkedList *list, int item, int pos);

void popBegin(LinkedList *list);

void popEnd(LinkedList *list);

void popPos(LinkedList *list, int item, int pos);

void printLinkedList(LinkedList *list);

void getMinMax(LinkedList *list);

void findItem(LinkedList *list, int item);

void changeItem(LinkedList *list, int item, int pos);

void sortLinkedList(LinkedList *list);

void concatLinkedList(LinkedList *list1, LinkedList *list2);

void mergeLinkedList(LinkedList *list1, LinkedList *list2);

#endif