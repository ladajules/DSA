#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *front, *rear;
} Queue;

Queue *init() {
    Queue *q = malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

bool isEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, int val) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    if(isEmpty(q)) {
        q->front = q->rear = newNode; 
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue *q) {
    int item;
    if(isEmpty(q)) {
        printf("empty.\n");
        item = -1;
    } else {
        Node *temp = q->front;
        item = q->front->data;
        q->front = q->front->next;
        free(temp);

        if (q->front == NULL) {
            q->rear = NULL;
        }
    }
    return item;
}

int front(Queue *q) {
    if(isEmpty(q)) return -1;
    return q->front->data;
}

void display(Queue *q) {
    if(isEmpty(q)) {
        printf("empty.\n");
    } else {
        Queue *temp;
        temp = init();

        while(!isEmpty(q)) {
            printf("%d - ", front(q));
            enqueue(temp, dequeue(q));
        }
        
        while (!isEmpty(temp)) {
            enqueue(q, dequeue(temp));
        }
    }
}

int main() {
    Queue *q = init();

    printf("=== Initial State ===\n");
    display(q); 
    printf("isEmpty? %s\n\n", isEmpty(q) ? "true" : "false");

    printf("=== Enqueue Elements ===\n");
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display(q); 
    printf("Front = %d\n\n", front(q)); 

    printf("=== Dequeue One ===\n");
    printf("Dequeued: %d\n", dequeue(q)); 
    display(q); 
    printf("Front = %d\n\n", front(q)); 

    printf("=== Enqueue More ===\n");
    enqueue(q, 40);
    enqueue(q, 50);
    display(q); 
    printf("Front = %d\n\n", front(q));

    printf("=== Dequeue All ===\n");
    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeue(q));
    }
    display(q); 
    printf("isEmpty? %s\n\n", isEmpty(q) ? "true" : "false");

    printf("=== Try Dequeue/Front on Empty ===\n");
    printf("Dequeued: %d\n", dequeue(q)); 
    printf("Front = %d\n", front(q));    

    return 0;
}

