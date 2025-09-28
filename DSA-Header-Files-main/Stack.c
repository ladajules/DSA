#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "Studtype.h"

void initStack(STACK *S) {
    S->arr.top = -1;
    S->top = NULL;
}

Studtype stackPeekArray(arrSTACK S) {
    return S.stud[S.top];
}

Studtype stackPeekList(llSTACK *S) {
    return S->data;
}

void pushArr(STACK *S, Studtype data) {
    if (S->arr.top == STACKMAX - 1) {
        printf("Stack is full.\n");
    } else {
        S->arr.top++;
        S->arr.stud[S->arr.top] = data;
    }
}

void pushLL(STACK *S, Studtype data) {
    llSTACK *newNode = malloc(sizeof(llSTACK));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = data;
    newNode->next = S->top;
    S->top = newNode;
}

void popArr(STACK *S) {
    if (S->arr.top == -1) {
        printf("Stack is empty.\n");
    } else {
        S->arr.top--;
    }
}

void popLL(STACK *S) {
    if (S->top == NULL) {
        printf("Stack is empty.\n");
    } else {
        llSTACK *temp = S->top;
        S->top = S->top->next;
        free(temp);
    }
}

bool isDataInArrayStack(arrSTACK arr, Studtype data) {
    for (int i = 0; i <= arr.top; i++) {
        if (cmp(arr.stud[i], data)) {
            return true;
        }
    }
    return false;
}

bool isDataInLLStack(llSTACK *head, Studtype data) {
    llSTACK *curr = head;
    while (curr != NULL) {
        if (cmp(curr->data, data)) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

bool stackIsUnique(STACK S, Studtype data) {
    if (isDataInArrayStack(S.arr, data)) {
        return false;
    }
    
    if (isDataInLLStack(S.top, data)) {
        return false;
    }
    return true;
}

void popUnique(STACK *S, Studtype data) {
    if (S->arr.top == -1 && S->top == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    
    bool found = false;
    
    STACK tempStack;
    initStack(&tempStack);
    
    while (S->arr.top != -1 && !found) {
        Studtype tempData = stackPeekArray(S->arr);
        
        if (cmp(tempData, data)) {
            found = true;
            popArr(S);
        } else {
            pushArr(&tempStack, tempData);
            popArr(S);
        }
    }
    
    while (tempStack.arr.top != -1) {
        Studtype giveBak = stackPeekArray(tempStack.arr);
        pushArr(S, giveBak);
        popArr(&tempStack);
    }
    
    if (!found) {
        llSTACK *curr = S->top;
        llSTACK *prev = NULL;

        while (curr != NULL && !found) {
            if (cmp(curr->data, data)) {
                if (prev == NULL) {
                    S->top = curr->next;
                } else {
                    prev->next = curr->next;
                }

                free(curr);
                found = true;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    
    if (found) {
        printf("Popped.\n");
    } else {
        printf("Data not found in stack.\n");
    }
}

void pushUnique(STACK *S, Studtype data) {
    if (S->arr.top == STACKMAX - 1) {
        printf("Stack is full.\n");
        return;
    }
    
    if (stackIsUnique(*S, data)) {
        pushArr(S, data);
        
        pushLL(S, data);
        
        printf("Pushed.\n");
    } else {
        printf("Data is already in the stack.\n");
    }
}

void displayStack(STACK S) {
    if (S.arr.top == -1 && S.top == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    
    printf("\n=== Array Stack ===\n");
    printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
    for (int i = S.arr.top; i >= 0; i--) {
        Studtype data = S.arr.stud[i];
        printf("%-15s%-15s%-5c%-10d%-10s\n", 
            data.name.LName, 
            data.name.FName,
            data.name.Mi,
            data.YrLvl,
            data.Course);
    }

    printf("\n=== Linked-list Stack ===\n");
    printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
    llSTACK *curr = S.top;
    while (curr != NULL) {
        printf("%-15s%-15s%-5c%-10d%-10s\n", 
            curr->data.name.LName, 
            curr->data.name.FName,
            curr->data.name.Mi,
            curr->data.YrLvl,
            curr->data.Course);
        curr = curr->next;
    }
    
    printf("\n");
}