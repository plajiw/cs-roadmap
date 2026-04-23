#include <stdio.h>

typedef struct node
{
    int data;
    Node *reference;
} Node;

Node* createNode(int item, Node* next);
