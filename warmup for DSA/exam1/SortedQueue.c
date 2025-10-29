#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int data[MAX];
    int front;
    int rear;
} Queue;

int front(Queue *q) {
    return q->data[q->front];
}

void enqueue(Queue *q, int data) {
    if (q->front == -1) q->front = q->rear = 0; 
    else q->rear = (q->rear + 1) % MAX; 
    q->data[q->rear] = data;
}

int dequeue(Queue *q) {
    if (q->front == -1) return -1;
    int val = q->data[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front = (q->front + 1) % MAX;
    return val;
}

void enqueueSorted(Queue *q, int data) {
    if ((q->rear + 1) % MAX == q->front) return;
    Queue tmp; tmp.front = tmp.rear = -1;
    bool inserted = false;

    while(q->front != -1) {
        if(!inserted && data < front(q)) {
            enqueue(&tmp, data);
            inserted = true;
        }
        enqueue(&tmp, dequeue(q));
    }
    if(!inserted) enqueue(&tmp, data);

    while(tmp.front != -1) { enqueue(q, dequeue(&tmp)); }
}

void display (Queue *q) {
    if (q->front == -1) { printf("empty.\n"); return; }
    Queue tmp; tmp.front = tmp.rear = -1;
    while(q->front != -1) {
        int val = dequeue(q);
        printf("%d ", val);
        enqueue(&tmp, val);
    }
    while(tmp.front != -1) enqueue(q, dequeue(&tmp));
    printf("\n");
}

int main() {
    Queue q; q.front = q.rear = -1;

    enqueueSorted(&q, 30);
    enqueueSorted(&q, 90);
    enqueueSorted(&q, 50);
    enqueueSorted(&q, 70);
    enqueueSorted(&q, 10);

    display(&q);

    return 0;
}