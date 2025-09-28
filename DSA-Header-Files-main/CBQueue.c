#include <stdio.h>
#include <stdbool.h>
#include "CursorBased.h"
#include "CBQueue.h"
#include "Studtype.h"

void CBinitQueue(CBQueue *Q) {
    Q->front = Q->rear = -1;    
}

bool CBqueueIsEmpty(CBQueue Q) {
    return Q.front == -1;    
}

void CBenqueue(VHeap *VH, CBQueue *Q, Studtype data) {
    int newNode = allocSpace(VH);
    if (newNode != -1) {
        VH->H[newNode].data = data;
        VH->H[newNode].next = -1;
        
        if (Q->rear == -1) {
            Q->front = Q->rear = newNode;
        } else {
            VH->H[Q->rear].next = newNode;
            Q->rear = newNode;
        }
    } else {
        printf("Queue is full.\n");
    }
}

void CBdequeue(VHeap *VH, CBQueue *Q) {
    if (!CBqueueIsEmpty(*Q)) {
        int n = Q->front;
        Q->front = VH->H[n].next;
        
        if (Q->front == -1) {
            Q->rear = -1;
        }
        dealloc(VH, n);
    } else {
        printf("Queue is empty.\n");
    }    
}

Studtype CBfront(VHeap *VH, CBQueue Q) {
    return VH->H[Q.front].data;
}

bool CBqueueIsUnique(VHeap *VH, CBQueue *Q, Studtype data) {
    CBQueue temp; CBinitQueue(&temp);
    bool yer = true;
    
    while (!CBqueueIsEmpty(*Q) && yer) {
        Studtype t = CBfront(VH, *Q);
        if (cmp(t, data)) {
            yer = false;
        }
        CBenqueue(VH, &temp, t);
        CBdequeue(VH, Q);
    }
    
    while (!CBqueueIsEmpty(temp)) {
        Studtype x = CBfront(VH, temp);
        CBenqueue(VH, Q, x);
        CBdequeue(VH, &temp);
    }
    
    return yer;
}

void CBenqueueUnique(VHeap *VH, CBQueue *Q, Studtype data) {
    if (CBqueueIsUnique(VH, Q, data)) {
        CBenqueue(VH, Q, data);
        printf("Enqueued.\n");
    } else {
        printf("Already in the queue.\n");
    }    
}

void CBdequeueUnique(VHeap *VH, CBQueue *Q, Studtype data) {
    if (!CBqueueIsEmpty(*Q)) {
        CBQueue temp; CBinitQueue(&temp);
        bool bye = false;
        
        while (!CBqueueIsEmpty(*Q) && !bye) {
            Studtype x = CBfront(VH, *Q);
            CBdequeue(VH, Q);
            
            if (cmp(x, data)) {
                bye = true;
            } else {
                CBenqueue(VH, &temp, x);
            }
        }
        
        while (!CBqueueIsEmpty(temp)) {
            Studtype x = CBfront(VH, temp);
            CBenqueue(VH, Q, x);
            CBdequeue(VH, &temp);
        }
        
        if (bye) printf("Dequeued.\n");
        else printf("Not found.\n");
        
    } else {
        printf("Queue is empty.\n");
    }
}

void CBdisplayQueue(VHeap *VH, CBQueue *Q) {
    if (CBqueueIsEmpty(*Q)) {
        printf("Queue is empty.\n");
    } else {
        printf("\n=== Cursor-based Queue ===\n");
        printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
        
        CBQueue temp; CBinitQueue(&temp);
        
        while (!CBqueueIsEmpty(*Q)) {
            Studtype s = CBfront(VH, *Q);
            printf("%-15s%-15s%-5c%-10d%-10s\n", s.name.LName, s.name.FName, s.name.Mi, s.YrLvl, s.Course);
            CBenqueue(VH, &temp, s);
            CBdequeue(VH, Q);
        }
        
        while (!CBqueueIsEmpty(temp)) {
            Studtype x = CBfront(VH, temp);
            CBenqueue(VH, Q, x);
            CBdequeue(VH, &temp);
        }
        printf("\n");
    }
}