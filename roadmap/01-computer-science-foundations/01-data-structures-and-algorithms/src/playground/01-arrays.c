#include <stdio.h>

int main()
{
    int A[5];
    A[0] = 12;
    A[1] = 15;
    A[2] = 25;

    printf(sizeof(A));  // 20 bytes (5 * 4 bytes)
    printf(A[0]);       // 12
}