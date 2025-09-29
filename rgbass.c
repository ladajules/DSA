#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_SIZE 64

typedef char *String;

typedef struct {
    String colorName;
    int RGBval[3];
} Color;

typedef struct node {
    Color color;
    struct node *next;
} Node;

int RGB(int rgb[]) { return (rgb[0] + rgb[1] + rgb[2]) % 64; }

void initDictionary(Node **hashTable) {
    for(int i = 0; i < LIST_SIZE; i++) { hashTable[i] = NULL; }
}

void insert(Node **hashTable, Color color) {
    // default new node
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) exit(1);
    newNode->color = color;
    newNode->next = NULL;

    // hash
    int index = RGB(color.RGBval);

    if (!hashTable[index]) {
        hashTable[index] = newNode; // insert at head if head is null
    } else {
        Node *temp = hashTable[index]; // insert at last
        while(temp->next) { temp = temp->next; }
        temp->next = newNode;
    }
}

void deleteYo(Node **hashTable, Color color) {
    int index = RGB(color.RGBval);
    
    if (hashTable[index] == NULL) return;
    
    Node *temp = hashTable[index];
    if (strcmp(hashTable[index]->color.colorName, color.colorName) == 0) {
        Node *toDel = hashTable[index];
        hashTable[index] = hashTable[index]->next;
        free(toDel);
    } else {
        while (temp->next && strcmp(temp->next->color.colorName, color.colorName) != 0) { temp = temp->next; }
        Node *toDel = temp->next;
        temp->next = toDel->next;
        free(toDel);
    }
}

// void search() {} 

int main() {
    Node *hashTable[LIST_SIZE]; initDictionary(hashTable);
    Color colors[5] = {{"Blue", {0, 32, 255}}, 
                        {"Yellow", {255, 255, 0}},
                        {"Red", {255, 0, 0}},
                        {"Orange", {255, 165, 0}},
                        {"Black", {0, 0, 0}}};
    
    for (int i = 0; i < 5; i++) {
        insert(hashTable, colors[i]);
    }
    Color trial = {"Try", {0, 32, 255}}; // try to chain
    insert(hashTable, trial);

    for (int i = 0; i < LIST_SIZE; i++) { // dishplay
        if (hashTable[i] == NULL) { 
            printf("NULL\n");
        } else {
            Node *temp = hashTable[i];
            while (temp) {
                printf("%s -> ", temp->color.colorName);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
    
    deleteYo(hashTable, colors[0]); // works yo

    return 0;
}
