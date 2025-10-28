#include <stdio.h>
#include <stdlib.h>

#define SIZE 2 // two words per set
#define WORDSIZE (sizeof(unsigned int) * 8) // make it return into BITS
typedef unsigned int *Set;

Set initSet() {
    return calloc(SIZE, sizeof(unsigned int));
}

void insertElem(Set s, int elem) {
    int whichWord = elem / WORDSIZE;
    int whichBit = elem % WORDSIZE;
    s[whichWord] |= (1U << whichBit);
}

void deleteElem(Set s, int elem) {
    int whichWord = elem / WORDSIZE;
    int whichBit = elem % WORDSIZE;
    s[whichWord] &= ~(1U << whichBit);
}

int isMember(Set s, int elem) {
    int whichWord = elem / WORDSIZE;
    int whichBit = elem % WORDSIZE;
    return (s[whichWord] & (1U << whichBit)) != 0;
}

void displaySet(Set s) {
    for (int i = 0; i < SIZE * WORDSIZE; i++) {
        if (isMember(s, i)) printf("%d ", i);
    }
    printf("\n");
}

Set setUnion(Set a, Set b) {
    Set c = initSet();
    for (int i = 0; i < SIZE; i++) {
        c[i] = a[i] | b[i];  
    }
    return c;
}

Set setIntersection(Set a, Set b) {
    Set c = initSet();
    for (int i = 0; i < SIZE; i++) {
        c[i] = a[i] & b[i];
    }
    return c;
}

Set setDiff(Set a, Set b) {
    Set c = initSet();
    for (int i = 0; i < SIZE; i++) {
        c[i] = a[i] & ~b[i];
    }
    return c;
}

int main() {
    Set courseA = initSet();
    Set courseB = initSet();
    Set result = initSet();

    insertElem(courseA, 1);
    insertElem(courseA, 3);
    insertElem(courseA, 5);

    insertElem(courseB, 3);
    insertElem(courseB, 4);

    printf("Students in Course A: "); displaySet(courseA);
    printf("Students in Course B: "); displaySet(courseB);

    result = setUnion(courseA, courseB);
    printf("Union (A ∪ B): "); displaySet(result);

    result = setIntersection(courseA, courseB);
    printf("Intersection (A ∩ B): "); displaySet(result);

    result = setDiff(courseA, courseB);
    printf("Difference (A − B): "); displaySet(result);

    return 0;
}