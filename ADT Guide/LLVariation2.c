#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

List *init() {
    List *l = malloc(sizeof(List));
    l->head = NULL;
    l->count = 0;
    return l;
}

void empty(List *l) {
    while (l->head != NULL) {
        Node *temp;
        temp = l->head;
        l->head = l->head->next;
        free(temp);
        l->count--;
    }
    printf("List emptied.\n");
}

void insertFirst(List *l, int data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = l->head;
    l->head = newNode;
    l->count++;
}

void insertLast(List *l, int data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (l->head == NULL) {
        l->head = newNode;
    } else {
        Node *temp = l->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    l->count++;
}

void insertPos(List *l, int data, int index) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (index > l->count && index > 0) {
        printf("Invalid index.\n");
        free(newNode);
    } else if (index == 0) {
        insertFirst(l, data);
    } else if (index == l->count) {
        insertLast(l, data);
    } else {
        Node *temp;
        int i;
        for (temp = l->head, i = 0; temp != NULL && i < index - 1; temp = temp->next, i++) { }

        newNode->next = temp->next;
        temp->next = newNode;
        l->count++;
    }
}

void deleteStart(List *l) {
    Node *temp = l->head;
    l->head = temp->next;
    free(temp);
    l->count--;
}

void deleteLast(List *l) {
    if (l->count == 1) {
        free(l->head);
    } else {
        Node *temp;
        int i;
        for (temp = l->head, i = 0; temp != NULL && i < l->count - 2; temp = temp->next, i++) { }
        Node *toDel = temp->next;
        free(toDel);
        temp->next = NULL;
        l->count--;
    }
}

void deletePos(List *l, int index) {
    if (index == 0) {
        deleteStart(l);
    } else if (index == l->count) {
        deleteLast(l);
    } else {
        Node *temp;
        int i;
        for (temp = l->head, i = 0; temp != NULL && i < index - 1; temp = temp->next, i++) { }

        Node *toDel = temp->next;
        temp->next = toDel->next;
        free(toDel);
        l->count--;
    }
}

int retrieve(List *l, int index) {
    if (index < l->count && index > 0) {
        Node *temp;
        int i;
        for (temp = l->head, i = 0; temp != NULL && i < index; temp = temp->next, i++) { }

        return temp->data;
    } else {
        printf("Invalid index.\n");
        return -1;
    }
}

int locate(List *l, int data) {
    if (l->head == NULL) {
        return -1;
    } else {
        Node *temp;
        int i;
        for (temp = l->head, i = 0; temp != NULL && data != temp->data; temp = temp->next, i++) { }

        return i;
    }
}

int main() {
    List *l = init();

    printf("=== InsertFirst Tests ===\n");
    insertFirst(l, 10);
    insertFirst(l, 20);
    insertFirst(l, 30); 
    printf("Head = %d, Count = %d\n", l->head->data, l->count);

    printf("\n=== InsertLast Tests ===\n");
    insertLast(l, 40);
    insertLast(l, 50);   
    printf("Tail after insertLast = %d, Count = %d\n", l->head->next->next->next->data, l->count);

    printf("\n=== InsertPos Tests ===\n");
    insertPos(l, 99, 0); 
    insertPos(l, 77, 3);  
    insertPos(l, 88, l->count);  
    insertPos(l, 123, 100);      
    printf("Count after insertPos = %d\n", l->count);

    printf("\n=== Retrieve Tests ===\n");
    printf("Retrieve index 0: %d\n", retrieve(l, 0));
    printf("Retrieve index 2: %d\n", retrieve(l, 2));
    printf("Retrieve invalid index: %d\n", retrieve(l, 99));

    printf("\n=== Locate Tests ===\n");
    printf("Locate value 40: %d\n", locate(l, 40));
    printf("Locate missing value 1000: %d\n", locate(l, 1000));

    printf("\n=== DeleteStart Tests ===\n");
    deleteStart(l); 
    printf("Head after deleteStart = %d, Count = %d\n", l->head->data, l->count);

    printf("\n=== DeleteLast Tests ===\n");
    deleteLast(l);  
    printf("Count after deleteLast = %d\n", l->count);

    printf("\n=== DeletePos Tests ===\n");
    deletePos(l, 0);      
    deletePos(l, l->count); 
    deletePos(l, 1);        
    printf("Count after deletePos = %d\n", l->count);

    printf("\n=== Empty List Tests ===\n");
    empty(l);
    printf("Count after empty = %d\n", l->count);

    return 0;
}