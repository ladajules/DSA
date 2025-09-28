#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int top;
} Stack;

Stack *init() {
    Stack *s = malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

bool isFull(Stack *s) {
    return s->top == MAX - 1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int data) {
    if (isFull(s)) {
        printf("full.\n");
    } else {
        s->top++;
        s->items[s->top] = data;
    }
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("empty.\n");
        return -1;
    } else {
        int item = s->items[s->top];
        s->top--;
        return item;
    }
}

int top(Stack *s) {
    return s->items[s->top];
}

void display(Stack *s) {
    if(isEmpty(s)) {
        printf("stack is empty.\n");
    } else {
        Stack t = *s;
        while (!isEmpty(&t)) {
            printf("%d - ", top(&t));
            int trash = pop(&t);
        }
    }
}

int main() {
    Stack *S = init();

    printf("=== Initial State ===\n");
    display(S);
    printf("isEmpty? %s\n\n", isEmpty(S) ? "true" : "false");

    printf("=== Push Elements ===\n");
    for (int i = 1; i <= MAX; i++) {
        push(S, i * 10);  
        printf("Pushed %d, top = %d\n", i * 10, top(S));
    }
    display(S);
    printf("isFull? %s\n\n", isFull(S) ? "true" : "false");

    printf("=== Try Push on Full Stack ===\n");
    push(S, 999);  
    printf("\n");

    printf("=== Pop Elements ===\n");
    for (int i = 0; i < MAX; i++) {
        printf("Popped %d\n", pop(S));
    }
    display(S);
    printf("isEmpty? %s\n\n", isEmpty(S) ? "true" : "false");

    printf("=== Try Pop on Empty Stack ===\n");
    pop(S);  

    return 0;
}

