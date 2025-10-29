#include <stdio.h>
#include "WarehouseInvSystem.h"

void init(Stack *s) {
    s->top = -1;
}

bool isFull(Stack *s) {
    return s->top == MAX - 1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if(isFull(s)) {
        printf("Stack is full.\n");
    } else {
        s->top++;
        s->value[s->top] = value;
    }
}

int peek(Stack *s) {
    return s->value[s->top];
}

int top(Stack *s) {
    return s->value[s->top];
}

int pop(Stack *s) {
    int item;
    if(isEmpty(s)) {
        printf("Stack is empty.\n");
    } else {
        item = peek(s);
        s->top--;
    }
    return item;
}

int search(Stack *s, int data) {
    int val = -1;
    if(isEmpty(s)) {
        val = -1;
    } else {
        Stack temp; init(&temp);

        while(!isEmpty(s)) {
            if (peek(s) == data) {
                val = peek(s);
            }
            push(&temp, pop(s));
        }

        while(!isEmpty(&temp)) {
            push(s, pop(&temp));
        }
    }

    return val;
}

void display(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
    } else {
        Stack tempStack; init(&tempStack);
        while(!isEmpty(s)) {
            int tempData = pop(s);
            printf("%d ", tempData);
            push(&tempStack, tempData);
        }

        while(!isEmpty(&tempStack)) {
            int giveBack = pop(&tempStack);
            push(s, giveBack);
        }
    }
    printf("\n");
}

int main() {
    Stack s[3];
    for(int i = 0; i < 3; init(&s[i++]));

    int choice, containerID;
    while (1) {
        printf("\n1. Add Container\n");
        printf("2. Remove Container\n");
        printf("3. Search container\n");
        printf("4. Display Warehouse\n");
        printf("5. Exit\n");
        printf("Choose an option: "); scanf("%d", &choice);

        switch(choice) {
            case 1:
            printf("Enter container ID: "); scanf("%d", &containerID);
            bool flag = false;
            for (int i = 0; i < 3 && !flag; i++) {
                if(!isFull(&s[i])) {
                    push(&s[i], containerID);
                    printf("Container %d added to Stack %d\n", containerID, i + 1);
                    flag = true;
                }
            }
            break;

            case 2:
            flag = false;
            for (int i = 0; i < 3; i++) {
                if(!isEmpty(&s[i]) && peek(&s[i]) == containerID) {
                    int removed = pop(&s[i]);
                    printf("Container %d removed from Stack %d\n", containerID, i + 1);
                    flag = true;
                }
            }
            break;
            
            case 3:
            int searchID, val;
            printf("Enter ID to search: "); scanf("%d", &searchID);
            int i;
            bool found = false;
            for (i = 0; i < 3 && !found; i++) {
                val = search(&s[i], searchID);
                if (val != -1) found = true;
            }
            (val != -1) ? printf("Container %d is found at Stack %d\n", val, i) : printf("Not found.\n");
            break;

            case 4:
            printf("\n==== Warehouse ====\n");
            for (int i = 0; i < 3; i++) {
                display(&s[i]);
            }
            break;

            case 5:
            printf("Exiting program...");
            return 1;
            break;

            default:
            printf("Invalid option.\n");
        }
    }
}

/* Guide Questions
From the MAIN function:
1. Write the code to create and initialize the three stacks (Tip: use an array!)
    Stack s[3];
    for(int i = 0; i < 3; init(&s[i++]));

2. Write the code for adding a container to the next available stack
    printf("Enter container ID: "); scanf("%d", &containerID);
    bool flag = false;
    for (int i = 0; i < 3 && !flag; i++) {
        if(!isFull(&s[i])) {
            push(&s[i], containerID);
            printf("Container %d added to Stack %d\n", containerID, i + 1);
            flag = true;
        }
    }

3. Write the code for removing a container from the latest stack
    flag = false;
    for (int i = 0; i < 3; i++) {
        if(!isEmpty(&s[i]) && peek(&s[i]) == containerID) {
            int removed = pop(&s[i]);
            printf("Container %d removed from Stack %d\n", containerID, i + 1);
            flag = true;
        }
    }

4. Write the code for checking if a container exists
    int search(Stack *s, int data) {
        int val = -1;
        if(isEmpty(s)) {
            val = -1;
        } else {
            Stack temp; init(&temp);

            while(!isEmpty(s)) {
                if (peek(s) == data) {
                    val = peek(s);
                }
                push(&temp, pop(s));
            }

            while(!isEmpty(&temp)) {
                push(s, pop(&temp));
            }
        }

        return val;
    }
*/