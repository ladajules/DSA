#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int data;
    int next;
} HeapSpace;

typedef struct {
    HeapSpace H[10];
    int avail;
} VHeap;

typedef int List;

void initVHeap(VHeap *v) {
    int i;
    for (i = 0; i < 9; i++) {
        v->H[i].next = i + 1;
    }
    v->H[i].next = -1;
    v->avail = 0;
}

int allocSpace(VHeap *v) {
    int ret = v->avail;
    if (ret != -1) {
        v->avail = v->H[ret].next;
    }
    return ret;
}

void dealloc(VHeap *v, int index) {
    if (index != -1) {
        v->H[index].next = v->avail;
        v->avail = index;
    }
}

void insertFirst(VHeap *v, List *L, int data) {
    int newNode = allocSpace(v);
    if (newNode == -1) {
        printf("Memory allocation failed.\n");
        //return
    }
    v->H[newNode].data = data;
    v->H[newNode].next = *L;
    *L = newNode;
}

void insertLast(VHeap *v, List *L, int data) {
    int newNode = allocSpace(v);
    if (newNode == -1) {
        printf("Memory allocation failed.\n");
        //return
    }

    int temp = *L;
    while (v->H[temp].next != -1) {
        temp = v->H[temp].next;
    }

    if (temp == -1) {
        printf("Error\n");
        //return
    } else {
        v->H[newNode].data = data;
        v->H[newNode].next = -1;
        v->H[temp].next = newNode;
    }
}

void insertPos(VHeap *v, List *L, int data, int pos) {
    if (pos == 1) {
        insertFirst(v, L, data);
        //return
    }

    int temp = *L;
    for ( int i = 1; v->H[temp].next != -1 && i < pos; i++, temp = v->H[temp].next );
    if (temp != -1) {
        int newNode = allocSpace(v);
        v->H[newNode].data = data;
        v->H[newNode].next = v->H[temp].next;
        v->H[temp].next = newNode;
    }
}

void deleteFirst(VHeap *v, List *L) {
    int temp = *L;
    *L = v->H[temp].next;
    dealloc(v, temp);
}

void deleteLast(VHeap *v, List *L) {
    int temp;
    for ( temp = *L; v->H[v->H[temp].next].next != -1; temp = v->H[temp].next );
    // while (v->H[v->H[temp].next].next != -1) {
    //     temp = v->H[temp].next;
    // }
    int toDel = v->H[temp].next;
    dealloc(v, toDel);
    v->H[temp].next = -1;
}

void deletePos(VHeap *v, List *L, int pos)  {
    int i, temp;
    for( i = 1, temp = *L ; v->H[temp].next != -1 && i < pos - 1 ; i++, temp = v->H[temp].next );

    if (i == 1) {
        deleteFirst(v, L);
    } else {
        int toDel = v->H[temp].next;
        v->H[temp].next = v->H[toDel].next;
        dealloc(v, toDel);
    }
}




int main() {
    VHeap v; initVHeap(&v);
    List L;
}
