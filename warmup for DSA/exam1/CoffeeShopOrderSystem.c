#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int orderId[MAX];
    int front, rear;
} Queue;

void init(Queue *q) {
    q->front = q->rear = -1;
}

void enqueue(Queue *q, int id) {
    if ((q->rear + 1) % MAX == q->front) {
        printf("queue full.\n");
    } else if (q->front == -1) {
        q->front = q->rear = 0;
        q->orderId[q->rear] = id;
    } else {
        q->rear = (q->rear + 1) % MAX;
        q->orderId[q->rear] = id;
    }
}

int dequeue(Queue *q) {
    int ret;
    if (q->front == -1) {
        printf("queue empty.\n");
        ret = -1;
    } else if (q->front == q->rear) {
        ret = q->orderId[q->front];
        q->front = q->rear = -1;
    } else {
        ret = q->orderId[q->front];
        q->front = (q->front + 1) % MAX;
    }
    return ret;
}

int main() {
    Queue q; init(&q);

    char command[10];
    while(1) {
        scanf("%s", command);

        if (strcmp(command, "ORDER") == 0) {
            int id;
            scanf("%d", &id);
            enqueue(&q, id);
        } else if (strcmp(command, "SERVE") == 0) {
            int ret = dequeue(&q);
            if (ret == -1) printf("NO_ORDER\n");
            else printf("%d\n", ret);
        } else if (strcmp(command, "END") == 0) {
            exit(1);
        }
    }
}

