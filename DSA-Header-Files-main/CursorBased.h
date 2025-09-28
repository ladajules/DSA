#ifndef CURSORBASED_H
#define CURSORBASED_H
#include <stdbool.h>
#include "Studtype.h"

#define CBMAX 50

typedef struct {
	Studtype data;
	int next;
} stype, HeapSpace[CBMAX];

typedef struct {
	HeapSpace H;
	int avail;
} VHeap;

typedef int CBList;

typedef struct {
    int top;
} CBStack;

typedef struct {
    int front;
    int rear;
} CBQueue;

void initVHeap(VHeap *VH);

int allocSpace(VHeap *VH);

void dealloc(VHeap *VH, int index);

#endif