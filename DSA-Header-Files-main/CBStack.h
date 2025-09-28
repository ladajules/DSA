#ifndef CBSTACK_H
#define CBSTACK_H
#include "CursorBased.h"
#include "Studtype.h"

void CBinitStack(CBStack *S);
bool CBstackIsEmpty(CBStack S);
void CBpush(VHeap *VH, CBStack *S, Studtype data);
void CBpop(VHeap *VH, CBStack *S);
Studtype CBpeek(VHeap *VH, CBStack S);

bool CBstackIsUnique(VHeap *VH, CBStack *S, Studtype data);
void CBpushUnique(VHeap *VH, CBStack *S, Studtype data);
void CBpopUnique(VHeap *VH, CBStack *S, Studtype data);
void CBdisplayStack(VHeap *VH, CBStack *S);

#endif