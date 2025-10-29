#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char card;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void init(Stack *s) {
    s->top = NULL;
}

char peek(Stack *s) {
    return s->top->card;
}

void pop(Stack *s) {
    if (s->top == NULL) {
        printf("empty.\n");
    } else {
        Node *toDel = s->top;
        s->top = toDel->next;
        free(toDel);
    }
}

void push(Stack *s, char card) {
    Node *newNode = malloc(sizeof(Node));
    if(!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->card = card;
    newNode->next = s->top;
    s->top = newNode;
}

void reverse(Stack *s) {
    if (s->top == NULL) {
        printf("empty.\n");
    } else {
        Stack temp; init(&temp);

        while (s->top != NULL) {
            push(&temp, peek(s));
            pop(s);
        }
        *s = temp;
    }
}

void display(Stack *s) {
    if (s->top == NULL) {
        printf("empty.\n");
    } else {
        Stack temp; init(&temp);

        while(s->top != NULL) {
            printf("%c ", peek(s));
            push(&temp, peek(s));
            pop(s);
        }

        while (temp.top != NULL) {
            push(s, peek(&temp));
            pop(&temp);
        }
    }
    printf("\n");
}

int main() {
    Stack s; init(&s);

    push(&s, 'C');
    display(&s);
    push(&s, 'B');
    display(&s);
    push(&s, 'A');
    display(&s);

    reverse(&s);
    display(&s);

    return 0;
}