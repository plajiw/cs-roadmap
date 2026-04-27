#include <stdio.h>

#ifndef NODE_H
#define NODE_H

typedef struct node
{
    int data;
    struct node *reference;
} Node;

Node* createNode(int item, Node* next);

#endif
