#include <stdio.h>
#include <node.h>

Node *createNode(int item, Node *next)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->data = item;
        newNode->reference = next;
    }
}