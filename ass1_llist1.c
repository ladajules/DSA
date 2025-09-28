#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *next;
} Node;

Node *createNode (char data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void insertChar (Node **head, char data) {
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
    while (temp->next != NULL && !(temp->data <= newNode->data && newNode->data <= temp->next->data)) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void display(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node *head = NULL;

    // populate
    insertChar(&head, 'A');
    insertChar(&head, 'F');
    insertChar(&head, 'H');
    insertChar(&head, 'L');
    insertChar(&head, 'P');
    insertChar(&head, 'S');

    // insert G
    insertChar(&head, 'G');

    // display for test purposes
    printf("Linked List: ");
    display(head);

    return 0;
}