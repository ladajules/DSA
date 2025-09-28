#ifndef PHARMAQUEUE_H
#define PHARMAQUEUE_H
#include <stdbool.h>

#define MAX 10

typedef struct {
    int data[MAX];
    int front, rear;
} Queue;

Queue *init();
void enqueue(Queue *q, int data);
int dequeue(Queue *q);
bool isFull(Queue *q);
bool isEmpty(Queue *q);
void display(Queue *q);
#endif