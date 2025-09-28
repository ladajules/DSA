#include <stdio.h>

#define SIZE (sizeof(unsigned char) * 8)
typedef unsigned char SET;

SET set_union(SET A, SET B) { return A | B; }
SET set_intersection(SET A, SET B) { return A & B; }
SET set_difference(SET A, SET B) { return A & ~B; }
SET set_merge(SET A, SET B) { return set_union(A, B); }
SET add(SET A, int elem) { return A | (1U << elem); }

void display(SET A) {
    for (int i = 0; i < SIZE; i++) {
        if (A & (1U << i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    SET A = 0, B = 0;

    A = add(A, 1);
    A = add(A, 3);
    A = add(A, 7);

    B = add(B, 3);
    B = add(B, 4);
    B = add(B, 7);

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

    return 0;
}