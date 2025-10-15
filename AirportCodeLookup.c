#include <stdio.h>
#include <string.h>

#define TOTAL_SIZE 20

typedef struct {
    char code[4];
    int next;
} HeapSpace;

typedef struct {
    HeapSpace primary[10];
    HeapSpace secondary[10];
    int avail;
} VHeap;

void initVHeap(VHeap *v) {
    int i;
    for (i = 0; i < 10; i++) {
        strcpy(v->primary[i].code, "");
        v->primary[i].next = -1;
    }

    for (i = 0; i < 9; i++) {
        strcpy(v->secondary[i].code, "");
        v->secondary[i].next = i + 1;
    }
    strcpy(v->secondary[i].code, "");
    v->secondary[i].next = -1;

    v->avail = 0;
}

int allocSpace(VHeap *v) {
    int ret = v->avail;
    if (ret != -1) {
        v->avail = v->secondary[ret].next;
        v->secondary[ret].next = -1;
    }
    return ret + 10;
}

int hash(char code[4]) { return ((code[0] - 'A') * 26 * 26 + (code[1] - 'A') * 26 + (code[2] - 'A')) % 10; }

void insert(VHeap *v, char code[4]) {
    int i = hash(code);

    if (strlen(v->primary[i].code) == 0) {
        strcpy(v->primary[i].code, code);
        v->primary[i].next = -1;
        return;
    }

    int *nextPtr = &v->primary[i].next;
    while (*nextPtr != -1) {
        int secondaryIdx = *nextPtr - 10;
        nextPtr = &v->secondary[secondaryIdx].next;
    }

    int newNode = allocSpace(v);
    strcpy(v->secondary[newNode - 10].code, code);
    v->secondary[newNode - 10].next = -1;
    *nextPtr = newNode;
}

void printHeap(VHeap *heap) {
    int i;
    
    printf("\n=== FINAL STATE OF VIRTUAL HEAP ===\n\n");
    
    printf("PRIMARY AREA:\n");
    printf("Index | Element | Next\n");
    printf("------|---------|------\n");
    for (i = 0; i < 10; i++) {
        printf("  %d   | %-7s | %d\n", i, 
               strlen(heap->primary[i].code) > 0 ? heap->primary[i].code : "EMPTY",
               heap->primary[i].next);
    }
    
    printf("\nSECONDARY AREA (Overflow):\n");
    printf("Index | Element | Next\n");
    printf("------|---------|------\n");
    for (i = 0; i < 10; i++) {
        int displayNext = heap->secondary[i].next;
        if (displayNext != -1) displayNext += 10;
        printf(" %2d   | %-7s | %d\n", i + 10, 
               strlen(heap->secondary[i].code) > 0 ? heap->secondary[i].code : "EMPTY",
               strlen(heap->secondary[i].code) > 0 ? heap->secondary[i].next : displayNext);
    }
    
    printf("\nAvail pointer: %d\n", heap->avail == -1 ? -1 : heap->avail + 10);
}

void printHashIndices(char *codes[], int count) {
    int i;
    
    printf("\n=== HASH INDEX FOR EACH CODE ===\n\n");
    printf("Airport Code | Hash Index\n");
    printf("-------------|------------\n");
    for (i = 0; i < count; i++) {
        printf("    %-8s | %d\n", codes[i], hash(codes[i]));
    }
}

int main() {
    VHeap heap; initVHeap(&heap);
    char *codes[] = {"JFK", "LAX", "SFO", "CDG", "LHR", "NRT", 
                    "ATL", "DXB", "PEK", "MIA", "SYD", "ORD"};
    
    for (int i = 0; i < 15; i++) {
        insert(&heap, codes[i]);
    }

    printHeap(&heap);
    printHashIndices(codes, 15);

    return 0;
}



