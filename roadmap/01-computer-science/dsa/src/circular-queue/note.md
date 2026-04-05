# Fila Circular

## Estrutura da Fila Circular

```c

typedef struct queue
{
    int* data;      // ponteiro para o vetor alocado dinamicamente
    int front;      // índice do primeiro elemento 
    int rear;       // índice do último elemento
    int size;       // quantidade atual de elementos
    int capacity;   // tamanho máximo do vetor
} CircularQueue;

```

## 
