#include <stdio.h>
#include "linked-list.c"

int main()
{
    LinkedList list;

    initLinkedList(&list);

    pushBegin(&list, 3);
    pushBegin(&list, 2);
    pushBegin(&list, 1);
    pushEnd(&list, 4);
    pushEnd(&list, 5);

    printf("Lista: ");
    printLinkedList(&list);

    printf("Inserir 99 na posicao 2\n");
    pushPos(&list, 99, 2);

    printf("Lista: ");
    printLinkedList(&list);

    popBegin(&list);
    printf("Apos popBegin: ");
    printLinkedList(&list);

    popEnd(&list);
    printf("Apos popEnd: ");
    printLinkedList(&list);

    popPos(&list, 1);
    printf("Apos popPos(1): ");
    printLinkedList(&list);

    getMinMax(&list);

    findItem(&list, 3);
    findItem(&list, 99);

    printf("Alterando posicao 0 para 10\n");
    changeItem(&list, 10, 0);

    printf("Lista: ");
    printLinkedList(&list);

    sortLinkedList(&list);
    printf("Ordenada: ");
    printLinkedList(&list);

    LinkedList list2;
    initLinkedList(&list2);
    pushEnd(&list2, 7);
    pushEnd(&list2, 8);
    pushEnd(&list2, 9);

    printf("Lista2: ");
    printLinkedList(&list2);

    concatLinkedList(&list, &list2);
    printf("Apos concat: ");
    printLinkedList(&list);

    LinkedList listA, listB;
    initLinkedList(&listA);
    initLinkedList(&listB);

    pushEnd(&listA, 1);
    pushEnd(&listA, 3);
    pushEnd(&listA, 5);

    pushEnd(&listB, 2);
    pushEnd(&listB, 4);
    pushEnd(&listB, 6);

    printf("ListaA: ");
    printLinkedList(&listA);

    printf("ListaB: ");
    printLinkedList(&listB);

    mergeLinkedList(&listA, &listB);
    printf("Apos merge: ");
    printLinkedList(&listA);

    emptyLinkedList(&list);
    emptyLinkedList(&listA);

    getchar();
    return 0;
}
