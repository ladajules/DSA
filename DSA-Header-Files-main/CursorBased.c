#include <stdbool.h>
#include "CursorBased.h"

void initVHeap(VHeap *VH) {
    int i;
    for (i = 0; i < CBMAX - 1; i++) {
        VH->H[i].next = i + 1;
    }
    VH->H[i].next = -1;
    VH->avail = 0;
}

int allocSpace(VHeap *VH) {
    int retVal = VH->avail;
    if (VH->avail != -1) {
        VH->avail = VH->H[retVal].next;
    }
    return retVal;
}

void dealloc(VHeap *VH, int index) {
    if (index != -1 && index < CBMAX) {
        VH->H[index].next = VH->avail;
        VH->avail = index;
    }
}
