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
        v->primary[i].next = -1;
        strcpy(v->primary[i].code, "");
    }

    for (i = 0; i < 9; i++) {
        v->secondary[i].next = i + 1;
        strcpy(v->secondary[i].code, "");
    }
    v->secondary[i].next = -1;
    strcpy(v->secondary[i].code, "");

    v->avail = 0;
}

int allocSpace(VHeap *v) {
    int ret = v->avail;
    v->avail = v->secondary[ret].next;
    v->secondary[ret].next = -1;
    return ret;
}

int hash(char code[4]) { return ((code[0] - 'A') * 26 * 26 + (code[1] - 'A') * 26 + (code[2] - 'A')) % 10; }

void insert(VHeap *v, char code[4]) {
    int index = hash(code);

    if (strlen(v->primary[index].code) == 0) {
        strcpy(v->primary[index].code, code);
        v->primary[index].next = -1;
    } else {
        int newNode = allocSpace(v);
        strcpy(v->secondary[newNode].code, code);
        v->secondary[newNode].next = -1;

        if (v->primary[index].next == -1) {
            v->primary[index].next = newNode;
        } else {
            int nextPtr = v->primary[index].next;
            int prev = -1;
            while(nextPtr != -1) {
                prev = nextPtr;
                nextPtr = v->secondary[prev].next;
            }
            v->secondary[prev].next = newNode;
        }
    }
}

void printHeap(VHeap *heap) {
    int i;

    printf("\n=== FINAL STATE OF VIRTUAL HEAP ===\n\n");

    printf("PRIMARY AREA:\n");
    printf("Index | Element | Next\n");
    printf("------|---------|------\n");
    for (i = 0; i < 10; i++) {
        const char *elem = strlen(heap->primary[i].code) > 0 ? heap->primary[i].code : "EMPTY";
        int next = heap->primary[i].next;
        int displayNext = (next == -1) ? -1 : (next + 10);
        printf("  %d   | %-7s | %d\n", i, elem, displayNext);
    }

    printf("\nSECONDARY AREA (Overflow):\n");
    printf("Index | Element | Next\n");
    printf("------|---------|------\n");
    for (i = 0; i < 10; i++) {
        const char *elem = strlen(heap->secondary[i].code) > 0 ? heap->secondary[i].code : "EMPTY";
        int next = heap->secondary[i].next;
        int displayNext = (next == -1) ? -1 : (next + 10);
        printf(" %2d   | %-7s | %d\n", i + 10, elem, displayNext);
    }

    printf("\nAvail pointer: %d\n", heap->avail == -1 ? -1 : heap->avail + 10);
}

void printHashIndices(char *codes[], int count) {
    printf("\n=== HASH INDEX FOR EACH CODE ===\n\n");
    printf("Airport Code | Hash Index\n");
    printf("-------------|------------\n");
    for (int i = 0; i < count; i++) {
        printf("    %-8s | %d\n", codes[i], hash(codes[i]));
    }
}

int main() {
    VHeap heap; initVHeap(&heap);
    char *codes[] = {"JFK", "LAX", "SFO", "CDG", "LHR", "NRT", 
                    "ATL", "DXB", "PEK", "MIA", "SYD", "ORD"};
    
    for (int i = 0; i < 12; i++) {
        insert(&heap, codes[i]);
    }

    printHeap(&heap);
    printHashIndices(codes, 12);

    return 0;
}