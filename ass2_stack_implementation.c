#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    char elem[MAX];
    int top;
} STACK;

bool isEmpty(STACK s) {
    bool flag = false;
    if (s.top == -1) {
        flag = true;
    }

    return flag;
}

bool isFull(STACK s) {
    bool flag = false;
    if (s.top == MAX - 1) {
        flag = true;
    }

    return flag;
}

char top(STACK s) {
    return s.elem[s.top];
}

void peek(STACK s) {
    printf("%c ", s.elem[s.top]);
}

void pop(STACK *s) {
    if (isEmpty(*s)) {
        printf("Stack is empty. Nothing to pop.\n");
    } else {
        s->top--;
    }
}

bool isUnique(STACK *s, char data) {
    bool flag = false;

    STACK temp = *s;

    while (temp.top != -1 && flag == false) {
        char compare = top(temp);
        if (compare == data) {
            flag = true;
        }
        pop(&temp);
    }

    return flag;
}

void push(STACK *s, char data) {
    if (isFull(*s)) {
        printf("Stack is full.\n");
    } else {
        if (isUnique(s, data)) {
            printf("%c is already in the stack.\n", data);
        } else {
            s->top++;
            s->elem[s->top] = data;
            printf("%c has been pushed to the stack.\n", s->elem[s->top]);
        }
    }
}

void display(STACK s) {
    STACK temp = s;
    if (isEmpty(s)) {
        printf("Stack is empty. Nothing to display.\n");
    } else {
        while (temp.top != -1) {
            peek(temp);
            pop(&temp);
        }
    }
    printf("\n");
}

int main() {
    STACK s;
    s.top = -1;

    push(&s, 'A');
    push(&s, 'C');
    push(&s, 'F');
    display(s);

    push(&s, 'F');

    return 0;
}