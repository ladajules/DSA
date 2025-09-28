#include <stdio.h>
#include "PharmaQueueSystem.h"
#include <stdbool.h>
#include <stdlib.h>

Queue *init() {
    Queue *q = malloc(sizeof(Queue));
    q->front = q->rear = -1;
    return q;
}

void enqueue(Queue *q, int data) {
    if(isFull(q)) {
        printf("Queue is full.\n");
    } else if (isEmpty(q)) {
        q->front = q->rear = 0;
        q->data[q->rear] = data;
    } else {
        q->rear = (q->rear + 1) % MAX;
        q->data[q->rear] = data;
    }
}

int dequeue(Queue *q) {
    int ret;
    if(isEmpty(q)) {
        ret = -1;
    } else if (q->front == q->rear) {
        ret = q->data[q->front];
        q->front = q->rear = -1;
    } else {
        ret = q->data[q->front];
        q->front = (q->front + 1) % MAX;
    }
    return ret;
}

bool isFull(Queue *q) {
    return (q->rear + 1) % MAX == q->front;
}

bool isEmpty(Queue *q) {
    return q->front == -1;
}

void display(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
    } else {
        Queue *tempQ = init();
        while(!isEmpty(q)) {
            int tempData = dequeue(q);
            printf("%d - ", tempData);
            enqueue(tempQ, tempData);
        }

        while(!isEmpty(tempQ)) {
            int tempD = dequeue(tempQ);
            enqueue(q, tempD);
        }
        free(tempQ);
    }
    printf("\n");
}

int main() {
    Queue *prioQueue = init();
    Queue *regQueue = init();
    int prioCount = 0, regCount = 0;

    int choice;
    while(1) {
        printf("\n1. Add Customer\n2. Call Customer\n3. Display Queue\n4. Exit\nOption: "); scanf("%d", &choice);

        switch (choice) {
            case 1:
            int wut;
            printf("Priority (1) or Regular (2): "); scanf("%d", &wut);

            int data;
            if (wut == 1 && !isFull(prioQueue)) {
                data = 1001 + prioCount;
                enqueue(prioQueue,  data);
                prioCount++;
            } else {
                data = 2001 + regCount;
                enqueue(regQueue, data);
                regCount++;
            }
            break;

            case 2:
            if (!isEmpty(prioQueue)) {
                int num = dequeue(prioQueue);
                if (num == -1) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Calling customer %d...\n", num);
                }
                prioCount--;
            } else {
                int num = dequeue(regQueue);
                if (num == -1) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Calling customer %d...\n", num);
                }
                regCount--;
            }
            break;

            case 3:
            printf("=== Priority Queue ===\n"); 
            display(prioQueue);
            printf("=== Regular Queue ===\n"); 
            display(regQueue);
            break;

            case 4:
            printf("Exiting program...");
            return 1;
            break;

            default:
            printf("Invalid option.\n");
        }
    }

    return 0;
}

/* GUIDE QUESTIONS
1. Write the code to declare and initialize the two queues
    Queue *prioQueue = init();
    Queue *regQueue = init();

2. Write the code for entering the regular queue
    if (wut == 1 && !isFull(prioQueue)) {
        data = 1001 + prioCount;
        enqueue(prioQueue,  data);
        prioCount++;
    } else {
        data = 2001 + regCount;
        enqueue(regQueue, data);
        regCount++;
    }

3. Write the code for entering the priority queue
    if (wut == 1 && !isFull(prioQueue)) {
        data = 1001 + prioCount;
        enqueue(prioQueue,  data);
        prioCount++;
    } else {
        data = 2001 + regCount;
        enqueue(regQueue, data);
        regCount++;
    }

4. Write the code for calling the next customer
    if (!isEmpty(prioQueue)) {
        int num = dequeue(prioQueue);
        if (num == -1) {
            printf("Queue is empty.\n");
        } else {
            printf("Calling customer %d...\n", num);
        }
        prioCount--;
    } else {
        int num = dequeue(regQueue);
        if (num == -1) {
            printf("Queue is empty.\n");
        } else {
            printf("Calling customer %d...\n", num);
        }
        regCount--;
    }
*/