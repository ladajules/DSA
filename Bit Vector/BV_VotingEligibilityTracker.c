#include <stdio.h>

#define MAX 128

typedef struct {
    unsigned int bits[MAX / 32];  // 4 computer words for 128 bits
} Set;

void initSet(Set *s) {
    for (int i = 0; i < MAX / 32; i++) {
        s->bits[i] = 0;
    }
}

void markEligible(Set *s, int id) {
    int whichWord = id / 32;
    int whichBit = id % 32;
    s->bits[whichWord] |= (1U << whichBit);
}

void revokeEligible(Set *s, int id) {
    int whichWord = id /32;
    int whichBit = id % 32;
    s->bits[whichWord] &= ~(1U << whichBit);
}

int isEligible(Set s, int id) {
    int whichWord = id / 32;
    int whichBit = id % 32;
    return (s.bits[whichWord] & (1U << whichBit)) != 0;
}

void displayEligible(Set s) {
    for (int i = 0; i < MAX; i++) {
        if (isEligible(s, i)) printf("%d ", i);
    }
    printf("\n");
}

Set combineEligible(Set a, Set b) {
    Set c; initSet(&c);
    for (int i = 0; i < MAX / 32; i++) {
        for (int j = 0; j < MAX; j++) {
            c.bits[i] = a.bits[i] | b.bits[i];
        }
    }
    return c;
}

Set commonEligible(Set a, Set b) {
    Set c; initSet(&c);
    for (int i = 0; i < MAX / 32; i++) {
        for (int j = 0; j < MAX; j++) {
            c.bits[i] = a.bits[i] & b.bits[i];
        }
    }
    return c;
}

int main() {
    Set regionA, regionB, result;

    initSet(&regionA);
    initSet(&regionB);

    markEligible(&regionA, 10);
    markEligible(&regionA, 20);
    markEligible(&regionA, 30);

    markEligible(&regionB, 20);
    markEligible(&regionB, 25);
    markEligible(&regionB, 30);

    printf("Region A Eligible IDs: "); displayEligible(regionA);
    printf("Region B Eligible IDs: "); displayEligible(regionB);

    result = combineEligible(regionA, regionB);
    printf("All Eligible (Union): "); displayEligible(result);

    result = commonEligible(regionA, regionB);
    printf("Common Eligible (Intersection): "); displayEligible(result);

    return 0;
}