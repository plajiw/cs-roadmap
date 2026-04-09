
#ifndef NODE_H
#define NODE_H

typedef struct node
{
    int value;
    struct node *next;
} Node;

Node *createNode(int item, Node *ptr);

#endif
