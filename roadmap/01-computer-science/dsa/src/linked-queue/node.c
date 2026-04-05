#include <stdlib.h>
#include "node.h"

Node *createNode(int item, Node *ptr)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->value = item;
        newNode->next = ptr;
    }
    return newNode;
}