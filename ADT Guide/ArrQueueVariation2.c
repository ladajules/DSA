#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue *init() {
    Queue *q = malloc(sizeof(Queue));
    q->front = q->rear = -1;
    return q;
}

bool isEmpty(Queue *q) {
    return q->front == -1 && q->rear == -1;
}

bool isFull(Queue *q) {
    return q->front == (q->rear + 2) % MAX;
}

void enqueue(Queue *q, int val) {
    if(isFull(q)) {
        printf("full.\n");
    } else if (isEmpty(q)) {
        q->front = q->rear = 0;
        q->items[q->rear] = val;
    } else {
        q->rear = (q->rear) + 1 % MAX;
        q->items[q->rear] = val;
    }
}

int dequeue(Queue *q) {
    int item = -1;
    if(isEmpty(q)) {
        printf("empty.\n");
    } else if (q->front == (q->rear + 1) % MAX) {
        item = q->items[q->front];
        q->front = q->rear = -1;
    } else {
        item = q->items[q->front];
        q->front = (q->front + 1) % MAX;
    }
    return item;
}

int front (Queue *q) {
    return q->items[q->front];
}

void display(Queue *q) {
    if(isEmpty(q)) {
        printf("empty.\n");
    } else {
        Queue t = *q;
        while (!isEmpty(&t)) {
            printf("%d - ", front(&t));
            int item = dequeue(&t);
        }
    }
}

int main() {
    Queue *q = init();

    printf("=== Initial State ===\n");
    display(q);  

    printf("\n=== Enqueue 5 elements ===\n");
    for (int i = 1; i <= 5; i++) {
        enqueue(q, i * 10);
    }
    display(q);  

    printf("\n=== Dequeue 2 elements ===\n");
    printf("Dequeued: %d\n", dequeue(q));
    printf("Dequeued: %d\n", dequeue(q));
    display(q); 

    printf("\n=== Enqueue more (wrap around test) ===\n");
    for (int i = 6; i <= 9; i++) {
        enqueue(q, i * 10);
    }
    display(q); 

    printf("\n=== Try enqueue on full queue ===\n");
    for (int i = 10; i <= 12; i++) {
        enqueue(q, i * 10); 
    }

    printf("\n=== Dequeue all elements ===\n");
    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeue(q));
    }
    display(q); 

    printf("\n=== Dequeue from empty queue ===\n");
    dequeue(q);  

    return 0;
}
