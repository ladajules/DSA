#ifndef QUEUE_H
#define QUEUE_H
#include "Studtype.h"
#include "Stack.h"
#include <stdbool.h>

#define QUEUEMAX 10

typedef struct {
    Studtype data[QUEUEMAX];
    int rear;
    int front;
} arrQUEUE;

typedef struct queueNode {
    Studtype data;
    struct queueNode *next;
} llQUEUE;

typedef struct {
    arrQUEUE arr;
    llQUEUE *front, *rear;
} Queue;

void initQueue(Queue *Q);
void enqueueUnique(Queue *Q, Studtype data);
void dequeueUnique(Queue *Q, Studtype data);
void displayQueue(Queue Q);
Studtype queueFrontArray(arrQUEUE Q);
Studtype queueFrontList(llQUEUE Q);
bool queueIsUnique(Queue Q, Studtype data);
void enqueueArr(Queue *Q, Studtype data);
void enqueueLL(Queue *Q, Studtype data);
void dequeueArr(Queue *Q);
void dequeueLL(Queue *Q);

#endif