#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int plate[10];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

bool isFull(Stack *s) {
    return s->top == 9;
}

int peek(Stack *s) {
    return s->plate[s->top];
}

void pop(Stack *s) {
    if (isEmpty(s)) {
        printf("empty.\n");
    } else {
        s->top--;
    }
}

void push(Stack *s, int data) {
    if (isFull(s)) {
        printf("full.\n");
    } else {
        s->top++;
        s->plate[s->top] = data;
    }
}

void pushSorted(Stack *s, int data) {
    if(isFull(s)) {
        printf("full.\n");
    } else if (isEmpty(s) || peek(s) > data) {
        push(s, data);
    } else {
        Stack temp; init(&temp);

        while (!isEmpty(s) && peek(s) < data) {
            push(&temp, peek(s));
            pop(s);
        }
        push(s, data);

        while(!isEmpty(&temp)) {
            push(s, peek(&temp));
            pop(&temp);
        }
    }
}

void display(Stack *s) {
    if(isEmpty(s)) {
        printf("empty.\n");
    } else {
        Stack temp; init(&temp);

        while (!isEmpty(s)) {
            int tempData = peek(s);
            printf("%d ", tempData);
            pop(s);
            push(&temp, tempData);
        }

        while (!isEmpty(&temp)) {
            int tempData = peek(&temp);
            pop(&temp);
            push(s, tempData);
        }
    }
    printf("\n");
}

int main() {
    Stack s; init(&s);

    int data[] = {3, 1, 2};
    for (int i = 0; i < 3; i++) {
        pushSorted(&s, data[i]);
        display(&s);
    }

    return 0;
}