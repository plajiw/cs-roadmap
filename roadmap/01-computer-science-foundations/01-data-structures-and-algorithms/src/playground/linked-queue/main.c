#include <stdio.h>
#include "queue.h"

int main() {
    Queue q;

    printf("Iniciando a Fila\n");
    initQueue(&q);

    printf("Enfileirando: 1, 2, 3\n");
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    
    printf("Estado atual da fila: ");
    printQueue(&q);

    int primeiro = firstElement(&q);
    printf("\nPrimeiro elemento: %d\n", primeiro);

    printf("Executar dequeue\n");
    dequeue(&q);

    primeiro = firstElement(&q);
    printf("Novo primeiro elemento após dequeue: %d\n", primeiro);

    printf("Estado atual da fila: ");
    printQueue(&q);

    printf("\nEnfileirando: 4, 5, 6\n");
    enqueue(&q, 4);
    enqueue(&q, 5);
    enqueue(&q, 6);

    printf("Estado atual da fila: ");
    printQueue(&q);

    int valorBusca = 3;
    int indice = indexElement(&q, valorBusca);

    printf("\nO elemento [%d] esta na posicao (indice): %d\n", valorBusca, indice);
    printf("\nO elemento [%d] nao foi encontrado.\n", valorBusca);

    printf("Limpar fila\n");
    eraseQueue(&q);
    
    printf("Fila finalizada com sucesso.\n");

    getchar();
    return 0;
}