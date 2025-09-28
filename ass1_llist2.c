#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node *createNode (int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void append (Node **head, int data) {
    Node *newNode = createNode(data);
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

bool search(Node *head, int b) {
    Node *temp = head;
    while (temp->next != NULL) {
        if (temp->data == b) {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

int main() {
    Node *head = NULL;

    // populate it
    append(&head, 10);
    append(&head, 20);
    append(&head, 30);

    int b = 20;
    if (search(head, b)) {
        printf("B (%d) is in the linked list.\n", b);
    } else {
        printf("B (%d) is NOT in the linked list.\n", b);
    }

    return 0;
}