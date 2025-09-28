#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Queue.h"
#include "Studtype.h"

void initQueue(Queue *Q) {
    Q->arr.front = Q->arr.rear = -1;
    Q->front = Q->rear = NULL;
}

Studtype queueFrontArray(arrQUEUE Q) { 
        return Q.data[Q.front];
}

Studtype queueFrontList(llQUEUE Q) {
    return Q.data;
}

bool queueIsUnique(Queue Q, Studtype data) {
    bool iFoundYou = true;
    
    Queue tempQueue;
    initQueue(&tempQueue);
    
    while (Q.arr.front != -1 && iFoundYou) {
        Studtype tempData = queueFrontArray(Q.arr);
        if (cmp(tempData, data)) {
            iFoundYou = false;
        }
        enqueueArr(&tempQueue, tempData);
        dequeueArr(&Q);
    }
    
    while (tempQueue.arr.front != -1) {
        Studtype give = queueFrontArray(tempQueue.arr);
        enqueueArr(&Q, give);
        dequeueArr(&tempQueue);
    }
    
    llQUEUE *tempHead = Q.front;
    while (tempHead != NULL && iFoundYou) {
        if (cmp(tempHead->data, data)) {
            iFoundYou = false;
        }
        tempHead = tempHead->next;
    }
    
    return iFoundYou;
}

void enqueueArr(Queue *Q, Studtype data) {
    if (Q->arr.front == -1) {
        Q->arr.front = Q->arr.rear = 0;
    } else {
        Q->arr.rear = (Q->arr.rear + 1) % QUEUEMAX;
    } 
    Q->arr.data[Q->arr.rear] = data;
}

void enqueueLL(Queue *Q, Studtype data) {
    llQUEUE *newNode = malloc(sizeof(llQUEUE));
    newNode->data = data;
    newNode->next = NULL;

    if (Q->front == NULL) {
        Q->front = Q->rear = newNode;
    } else {
        Q->rear->next = newNode;
        Q->rear = newNode;
    }
}

void dequeueArr(Queue *Q) {
    if (Q->arr.front == Q->arr.rear) {
        Q->arr.front = Q->arr.rear = -1;
    } else {
        Q->arr.front = (Q->arr.front + 1) % QUEUEMAX;
    }
}

void dequeueLL(Queue *Q) {
    llQUEUE *temp = Q->front;
    if (Q->front == Q->rear) {
        Q->front = Q->rear = NULL;
    } else {
        Q->front = Q->front->next;
    }
    free(temp);
}


void enqueueUnique(Queue *Q, Studtype data) {
    if (((Q->arr.rear + 1) % QUEUEMAX) == Q->arr.front) {
        printf("Queue is full.\n");
    } else {
        Queue tempQueue = *Q;
        if (queueIsUnique(tempQueue, data)) {
            enqueueArr(Q, data);
            enqueueLL(Q, data);
            
            printf("Queued.\n");
        } else {
            printf("Data is already in queue.\n");
        }
    }
}

void dequeueUnique(Queue *Q, Studtype data) {
    if ((Q->arr.front == -1) && Q->front == NULL) {
        printf("Queue is empty.\n");
    } else {
        // Array
        Queue tempQueue;
        initQueue(&tempQueue);
        bool flag = false;
        
        while (Q->arr.front != -1) {
            Studtype tempData = queueFrontArray(Q->arr);
            dequeueArr(Q);
            
            if (cmp(tempData, data) && !flag) {
                flag = true;
            }  else {
                enqueueArr(&tempQueue, tempData);
            }
        }
        
        while (tempQueue.arr.front != -1) {
            Studtype givMyData = queueFrontArray(tempQueue.arr);
            enqueueArr(Q, givMyData);
            dequeueArr(&tempQueue);
        }
        
        // Linked list
        llQUEUE *temp = Q->front, *prev = NULL;
        bool goodbyeMahFren = false;
        
        while (temp != NULL && !goodbyeMahFren) {
            if (cmp(temp->data, data)) {
                goodbyeMahFren = true;
                if (prev == NULL) {
                    Q->front = temp->next;
                } else {
                    prev->next = temp->next;
                    if (temp == Q->rear) {
                        Q->rear = prev;
                    }
                }
                llQUEUE *toDel = temp;
                temp = temp->next;
                free(toDel);
            } else {
                prev = temp;
                temp = temp->next;
            }
        }
        
        printf("Dequeued.\n");
    }
}

void displayQueue(Queue Q) {
    if (Q.arr.front == -1 && Q.front == NULL) {
        printf("Queue is empty.\n");
    } else {
        printf("\n=== Array Queue ===\n");
        printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
        Queue tempQueue;
        initQueue(&tempQueue);
        Studtype data;
        
        while (Q.arr.front != -1) {
            data = queueFrontArray(Q.arr);
            printf("%-15s%-15s%-5c%-10d%-10s\n", 
                    data.name.LName, 
                    data.name.FName,
                    data.name.Mi,
                    data.YrLvl,
                    data.Course);
            enqueueArr(&tempQueue, data);
            dequeueArr(&Q);
        }
        
        while (tempQueue.arr.front != -1) {
            Studtype give = queueFrontArray(tempQueue.arr);
            enqueueArr(&Q, give);
            dequeueArr(&tempQueue);
        }

        printf("\n=== Linked-list Queue ===\n");
        llQUEUE *temp = Q.front;
        printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
        while (temp != NULL) {
            printf("%-15s%-15s%-5c%-10d%-10s\n", 
                    temp->data.name.LName, 
                    temp->data.name.FName,
                    temp->data.name.Mi,
                    temp->data.YrLvl,
                    temp->data.Course);
            temp = temp->next;
        }
    }
    printf("\n");
}