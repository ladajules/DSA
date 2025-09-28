#ifndef CBQUEUE_H
#define CBQUEUE_H
#include <stdbool.h>
#include "CursorBased.h"
#include "Studtype.h"

void CBinitQueue(CBQueue *Q);
bool CBqueueIsEmpty(CBQueue Q);
void CBenqueue(VHeap *VH, CBQueue *Q, Studtype data);
void CBdequeue(VHeap *VH, CBQueue *Q);
Studtype CBfront(VHeap *VH, CBQueue Q);

bool CBqueueIsUnique(VHeap *VH, CBQueue *Q, Studtype data);
void CBenqueueUnique(VHeap *VH, CBQueue *Q, Studtype data);
void CBdequeueUnique(VHeap *VH, CBQueue *Q, Studtype data);
void CBdisplayQueue(VHeap *VH, CBQueue *Q);

#endif
