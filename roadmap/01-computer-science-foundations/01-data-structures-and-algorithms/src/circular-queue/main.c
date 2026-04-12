#include "circular-queue.h"
#include <stdio.h>

int main()
{
    CircularQueue q;
    int capacity = 7;

    initCircularQueue(&q, capacity);
    printf("Fila inicializada com tamanho maximo de %d\n\n", q.capacity);

    enqueue(&q, 101);
    enqueue(&q, 102);
    enqueue(&q, 103);
    enqueue(&q, 104);
    enqueue(&q, 105);
    enqueue(&q, 106);
    enqueue(&q, 107);
    enqueue(&q, 108); // Limite de tamanho

    printCircularQueue(&q);
    printf("size=%d front=%d rear=%d\n\n", q.size, front(&q), rear(&q));

    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    printCircularQueue(&q);
    printf("size=%d front=%d rear=%d\n\n", q.size, front(&q), rear(&q));

    enqueue(&q, 201);
    enqueue(&q, 202);
    enqueue(&q, 203);
    printCircularQueue(&q);
    printf("size=%d front=%d rear=%d\n\n", q.size, front(&q), rear(&q));

    printf("Primeiro valor: %d\n", first(&q));
    printf("Ultimo valor: %d\n\n", last(&q));

    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    printCircularQueue(&q);
    printf("size=%d front=%d rear=%d\n\n", q.size, front(&q), rear(&q));

    enqueue(&q, 301);
    enqueue(&q, 302);
    enqueue(&q, 303);
    enqueue(&q, 304);
    enqueue(&q, 305);
    printCircularQueue(&q);
    printf("size=%d front=%d rear=%d\n\n", q.size, front(&q), rear(&q));

    printf("Esta cheia: %s\n", isFull(&q) ? "sim" : "nao");

    // Obter indice
    int idx = indexElement(&q, 302);
    printf("Indice do 302: %d\n", idx);

    idx = indexElement(&q, 999);
    printf("Indice do 999: %d\n\n", idx); // não existe esse elemento

    printCircularQueue(&q);
    clearCircularQueue(&q);
    destroyCircularQueue(&q);

    return 0;
}
