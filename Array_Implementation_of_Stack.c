#include <stdio.h>
#include <stdlib.h>

#define MAX 4

int top = -1;

void print(int *arr) {
    int i;
    for (i = 0; i <= top; i++) {
        printf("%d ", arr[i]);
    }
}

void push(int *arr, int n) {
    if (top == MAX - 1) {
        printf("Stack is full.\n");
        return;
    }

    top++;
    arr[top] = n;

    print(arr);
}

int pop(int *arr) {
    if (top == -1) {
        printf("Stack underflow.\n");
        exit(1);
    }

    int value;
    value = arr[top];
    top--;

    print(arr);
    return value;
}

int main() {
    int stack_arr[MAX];
    int data;

    push(stack_arr, 1); 
    printf("\n");
    push(stack_arr, 3);
    printf("\n");
    push(stack_arr, 5);
    printf("\n");
    push(stack_arr, 9);
    printf("\n");

    data = pop(stack_arr);
    printf("\n");
    data = pop(stack_arr);

    return 0;
}