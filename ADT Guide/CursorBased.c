#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int data;
    int next;
} HeapSpace[MAX];

typedef struct {
    HeapSpace h;
    int avail;
} VHeap;

typedef int List;

void initialize(VHeap *v) {
    int i;
    for (i = 0; i < MAX - 1; i++) {
        v->h[i].next = i + 1;
    }
    v->h[i].next = -1;
    v->avail = 0;
}

int alloc(VHeap *v) {
    int ret = v->avail;
    if(ret != -1) {
        v->avail = v->h[ret].next;
    }
    return ret;
}

void dealloc(VHeap *v, int i) {
    if (i != -1 && i < MAX) {
        v->h[i].next = v->avail;
        v->avail = i;
    }
}

void insertFirst(VHeap *v, List *L, int data) {
    int newNode = alloc(v);
    v->h[newNode].data = data;
    v->h[newNode].next = *L;
    *L = newNode;
}

void insertLast(VHeap *v, List *L, int data) {
    int newNode = alloc(v);
    v->h[newNode].data = data;
    v->h[newNode].next = -1;

    if (*L == -1) {
        *L = newNode;
    } else {
        int temp;
        for (temp = *L; v->h[temp].next != -1; temp = v->h[temp].next) { }
        v->h[temp].next = newNode;

        // Node *temp = *head;
        // for (temp = *head; temp->next != NULL; temp = temp->next) { }
        // temp->next = newNode;
    }
}

void insertSorted(VHeap *v, List *L, int data) {
    int newNode = alloc(v);
    v->h[newNode].data = data;
    v->h[newNode].next = -1;

    if (*L == -1 || data <= v->h[*L].data) {
        v->h[newNode].next = *L;
        *L = newNode;
    } else {
        int prev;
        int curr;

        for (prev = *L, curr = v->h[prev].next; curr != -1 && data > v->h[curr].data; prev = curr, curr = v->h[curr].next) { }
        v->h[newNode].next = curr;
        v->h[prev].next = newNode;
    }
}

void delete(VHeap *v, List *L, int data) {
    int prev, curr;
    for (prev = -1, curr = *L; curr != -1 && v->h[curr].data != data; prev = curr, curr = v->h[curr].next);

    if (curr != -1) {
        if (prev == -1) {
            *L = v->h[curr].next;
        } else {
            v->h[prev].next = v->h[curr].next;
        }
        dealloc(v, curr);
    } else {
        printf("not found.\n");
    }
}

void deleteAllOccurrence(VHeap *v, List *L, int data) {
    int prev = -1;
    int curr = *L;

    while (curr != -1) {
        if (v->h[curr].data == data) {
            int toDel = curr;

            if (prev == -1) {
                *L = v->h[curr].next;
            } else {
                v->h[prev].next = v->h[curr].next;
            }

            curr = v->h[curr].next;
            dealloc(v, toDel);
        } else {
            prev = curr;
            curr = v->h[curr].next;
        }
    }
}

void display(VHeap v, List L) {
    if (L == -1) {
        printf("empty.\n");
    } else {
        for (int i = L; i != -1; i = v.h[i].next) {
            printf("%d - ", v.h[i].data);
        }
        printf("NULL\n");
    }
}

int main() {
    List L = -1;
    VHeap v;
    initialize(&v);

    printf("=== Test InsertFirst ===\n");
    insertFirst(&v, &L, 10);
    insertFirst(&v, &L, 20);
    insertFirst(&v, &L, 30);
    display(v, L); 

    printf("\n=== Test InsertLast ===\n");
    insertLast(&v, &L, 40);
    insertLast(&v, &L, 50);
    display(v, L); 

    printf("\n=== Test InsertSorted ===\n");
    insertSorted(&v, &L, 25);
    insertSorted(&v, &L, 5);
    insertSorted(&v, &L, 60);
    display(v, L); 

    printf("\n=== Test Delete (single occurrence) ===\n");
    delete(&v, &L, 10); 
    display(v, L);
    delete(&v, &L, 999); 

    printf("\n=== Test DeleteAllOccurrence ===\n");
    insertLast(&v, &L, 25);
    insertLast(&v, &L, 25);
    display(v, L); 
    deleteAllOccurrence(&v, &L, 25);
    display(v, L); 

    printf("\n=== Test Empty List Delete ===\n");
    List emptyList = -1;
    delete(&v, &emptyList, 10);  
    deleteAllOccurrence(&v, &emptyList, 10); 

    return 0;
}
