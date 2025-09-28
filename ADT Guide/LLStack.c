#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

Stack *init() {
    Stack *s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

bool isEmpty(Stack *s) {
    return s->top == NULL;
}

void push (Stack *s, int val) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack *s) {
    int item;
    if (isEmpty(s)) {
        printf("empty.\n");
        item = -1;
    } else {
        item = s->top->data;
        Node *trash = s->top;
        s->top = s->top->next;
        free(trash);
    }
    return item;
}

int peek(Stack *s) {
    if (isEmpty(s)) return -1;
    else return s->top->data;
}

void display(Stack *s) {
    if(isEmpty(s)) {
        printf("empty.\n");
    } else {
        Stack *temp;
        temp = init();

        while (!isEmpty(s)) {
            printf("%d - ", peek(s));
            push(temp, pop(s));
        }

        while (!isEmpty(temp)) {
            push(s, pop(temp));
        }
    }
}

int main() {
    Stack *s = init();

    printf("=== Initial State ===\n");
    display(s);
    printf("isEmpty? %s\n\n", isEmpty(s) ? "true" : "false");

    printf("=== Push Elements ===\n");
    push(s, 10);
    push(s, 20);
    push(s, 30);
    display(s);  
    printf("Top = %d\n\n", peek(s));

    printf("=== Pop One ===\n");
    printf("Popped %d\n", pop(s)); 
    display(s);  
    printf("Top = %d\n\n", peek(s));

    printf("=== Push More ===\n");
    push(s, 40);
    push(s, 50);
    display(s);  
    printf("Top = %d\n\n", peek(s));

    printf("=== Pop All ===\n");
    while (!isEmpty(s)) {
        printf("Popped %d\n", pop(s));
    }
    display(s);   
    printf("isEmpty? %s\n\n", isEmpty(s) ? "true" : "false");

    printf("=== Try Pop and Peek on Empty Stack ===\n");
    pop(s);  
    peek(s);  

    return 0;
}
