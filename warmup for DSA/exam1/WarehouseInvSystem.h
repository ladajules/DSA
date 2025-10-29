#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 5

typedef struct {
    int value[MAX];
    int top;
} Stack;

 void init(Stack *s);

 bool isFull(Stack *s);

 bool isEmpty(Stack *s);

 void push(Stack *s, int value);
 int peek(Stack *s);

 int top(Stack *s);

 int pop(Stack *s);
int search(Stack *s, int data);
 void display(Stack *s);
#endif