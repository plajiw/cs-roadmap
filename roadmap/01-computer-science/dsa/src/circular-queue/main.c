#include "circular-queue.h"
#include <stdio.h>

int main()
{
    CircularQueue q;
    int capacity = 7;

    initCircularQueue(&q, capacity);

    return 0;
}