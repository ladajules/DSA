#include <stdio.h>
#include <stdlib.h>

#define SIZE 4
#define WORDSIZE (sizeof(unsigned int) * 8)
typedef unsigned int *SET;

SET set_union(SET A, SET B) {
    SET C = calloc(SIZE, sizeof(unsigned int));
    for (int x = 0; x < SIZE; x++ ) {
        C[x] = A[x] | B[x];
    }
    return C;
}   

SET set_intersection(SET A, SET B) {
    SET C = calloc(SIZE, sizeof(unsigned int));
    for (int x = 0; x < SIZE; x++ ) {
        C[x] = A[x] & B[x];
    }
    return C;
}

SET set_difference(SET A, SET B) {
    SET C = calloc(SIZE, sizeof(unsigned int));
    for (int x = 0; x < SIZE; x++ ) {
        C[x] = A[x] & ~B[x];
    }
    return C;
}  

SET set_merge(SET A, SET B) {
    return set_union(A, B);
}  

void add(SET A, int elem) {
    int x = elem / WORDSIZE;
    int bit = elem % WORDSIZE;
    if (x < SIZE) {
        A[x] |= (1U << bit);
    }
}

void remove_elem(SET A, int elem) {
    int x = elem / WORDSIZE;
    int bit = elem % WORDSIZE;
    if (x < SIZE) {
        A[x] &= ~(1U << bit);
    }
}

void display(SET A) {
    for (int i = 0; i < SIZE * WORDSIZE; i++) {
        if (A[i / WORDSIZE] & (1U << (i % WORDSIZE))) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    SET A = calloc(SIZE, sizeof(unsigned int));
    SET B = calloc(SIZE, sizeof(unsigned int));

    add(A, 1);
    add(A, 3);
    add(A, 65);

    add(B, 3);
    add(B, 4);
    add(B, 65);

    printf("A: "); display(A);
    printf("B: "); display(B);

    SET C = set_union(A, B);
    SET D = set_intersection(A, B);
    SET E = set_difference(A, B);
    SET F = set_merge(A, B);

    printf("Union: "); display(C);
    printf("Intersection: "); display(D);
    printf("Difference: "); display(E);
    printf("Merge: "); display(F);

    free(A); free(B); free(C); free(D); free(E); free(F);
    return 0;
}