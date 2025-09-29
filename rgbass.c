#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

bool checkDaThang(Node **hashTable, Color color) {
    bool flag = false;
    for(int i = 0; i < LIST_SIZE && !flag; i++) {
        Node *temp = hashTable[i];
        while(temp && strcmp(temp->color.colorName, color.colorName) != 0) { temp = temp->next; }
        if (temp && strcmp(temp->color.colorName, color.colorName) == 0 && 
            temp->color.RGBval[0] == color.RGBval[0] &&
            temp->color.RGBval[1] == color.RGBval[1] &&
            temp->color.RGBval[2] == color.RGBval[2]) flag = true;
    }

    return flag;
}

void insert(Node **hashTable, Color color) {
    if (checkDaThang(hashTable, color)) {
        printf("Exact color and RGB value already in here dud.\n");
    } else {
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
        printf("Inserted.\n");
    }
}

void deleteYo(Node **hashTable, Color color) {
    int index = RGB(color.RGBval);
    bool deleted = false;
    
    if (hashTable[index] == NULL) {
        deleted = false;
    } else {
        Node *temp = hashTable[index];
        if (strcmp(hashTable[index]->color.colorName, color.colorName) == 0) {
            Node *toDel = hashTable[index];
            hashTable[index] = hashTable[index]->next;
            free(toDel);
            deleted = true;
        } else {
            while (temp->next && strcmp(temp->next->color.colorName, color.colorName) != 0) { temp = temp->next; }
            if (temp->next && strcmp(temp->next->color.colorName, color.colorName) == 0) {
                Node *toDel = temp->next;
                temp->next = toDel->next;
                free(toDel);
                deleted = true;
            }
        }
    }
    
    if (deleted) printf("Deleted.\n");
    else printf("Color cant be deleted. Not found.\n");
}

void search(Node **hashTable, Color color) {
    int index = RGB(color.RGBval);

    Node *temp = hashTable[index];
    while(temp && strcmp(temp->color.colorName, color.colorName) != 0) { temp = temp->next; }

    if (temp && strcmp(temp->color.colorName, color.colorName) == 0) {
        printf("Color %s is found at index %d with RGB(%d, %d, %d).\n", 
            temp->color.colorName, 
            index, 
            temp->color.RGBval[0], 
            temp->color.RGBval[1], 
            temp->color.RGBval[2]);
    } else {
        printf("Color %s not found.\n", color.colorName);
    }
}

void display(Node **hashTable) {
    for (int i = 0; i < LIST_SIZE; i++) { // dishplay
        if (hashTable[i] == NULL) { 
            printf("[%d] NULL\n", i);
        } else {
            Node *temp = hashTable[i];
            printf("[%d] ", i);
            while (temp) {
                printf("%s -> ", temp->color.colorName);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
    printf("\n");
}

void populateHashTable(Node **hashTable) {
    Color colors[80] = {{"Black", {0, 0, 0}},
                        {"Green", {0, 128, 0}},
                        {"Purple", {128, 0, 128}},
                        {"Gray", {128, 128, 128}},
                        {"Navy", {0, 0, 128}},
                        {"DarkGreen", {0, 64, 64}},
                        {"Teal", {0, 128, 128}},
                        {"DimGray", {64, 64, 64}},
                        {"Maroon", {128, 0, 1}},
                        {"DarkRed", {139, 0, 1}},
                        {"Wine", {114, 47, 1}},
                        {"Plum", {221, 160, 221}},
                        {"Orchid", {218, 112, 214}},
                        {"Thistle", {216, 191, 216}},
                        {"Chocolate", {210, 105, 30}},
                        {"SaddleBrown", {139, 69, 19}},
                        {"Peru", {205, 133, 63}},
                        {"Pink", {255, 192, 203}},
                        {"LightPink", {255, 182, 193}},
                        {"HotPink", {255, 105, 180}},
                        {"DeepPink", {255, 20, 147}},
                        {"Salmon", {250, 128, 114}},
                        {"LightSalmon", {255, 160, 122}},
                        {"DarkSalmon", {233, 150, 122}},
                        {"Coral", {255, 127, 80}},
                        {"Tomato", {255, 99, 71}},
                        {"OrangeRed", {255, 69, 0}},
                        {"Gold", {255, 215, 0}},
                        {"Goldenrod", {218, 165, 32}},
                        {"DarkGoldenrod", {184, 134, 11}},
                        {"Wheat", {245, 222, 179}},
                        {"BurlyWood", {222, 184, 135}},
                        {"Tan", {210, 180, 140}},
                        {"SkyBlue", {135, 206, 235}},
                        {"LightSkyBlue", {135, 206, 250}},
                        {"DeepSkyBlue", {0, 191, 255}},
                        {"Blue", {0, 32, 255}},
                        {"RoyalBlue", {65, 105, 225}},
                        {"SteelBlue", {70, 130, 185}},
                        {"MidnightBlue", {25, 25, 112}},
                        {"Orange", {255, 165, 0}},
                        {"DarkOrange", {255, 140, 0}},
                        {"Peach", {255, 229, 180}},
                        {"Olive", {128, 128, 42}},
                        {"OliveDrab", {107, 142, 35}},
                        {"YellowGreen", {154, 205, 50}},
                        {"SeaGreen", {46, 139, 87}},
                        {"MediumSeaGreen", {60, 179, 113}},
                        {"LightSeaGreen", {32, 178, 170}},
                        {"Turquoise", {64, 224, 208}},
                        {"MediumTurquoise", {72, 209, 204}},
                        {"PaleTurquoise", {175, 238, 238}},
                        {"Aquamarine", {127, 255, 212}},
                        {"MediumAquamarine", {102, 205, 170}},
                        {"Brown", {165, 42, 42}},
                        {"Sienna", {160, 82, 45}},
                        {"RosyBrown", {188, 143, 143}},
                        {"Lavender", {230, 230, 250}},
                        {"MediumPurple", {147, 112, 219}},
                        {"BlueViolet", {138, 43, 226}},
                        {"White", {255, 255, 255}},
                        {"Snow", {255, 250, 250}},
                        {"Ivory", {255, 255, 240}},
                        {"Beige", {245, 245, 220}},
                        {"Yellow", {255, 255, 0}},
                        {"Cyan", {0, 255, 255}},
                        {"Magenta", {255, 0, 255}},
                        {"Khaki", {240, 230, 140}},
                        {"LightYellow", {255, 255, 224}},
                        {"Red", {255, 0, 0}},
                        {"Lime", {0, 255, 0}},
                        {"Crimson", {220, 20, 60}},
                        {"FireBrick", {178, 34, 34}},
                        {"IndianRed", {205, 92, 92}},
                        {"Indigo", {75, 0, 130}},
                        {"Violet", {238, 130, 238}},
                        {"SlateBlue", {106, 90, 205}},
                        {"MediumSlateBlue", {123, 104, 238}},
                        {"SpringGreen", {0, 255, 127}},
                        {"ForestGreen", {34, 139, 34}}
    };
    
    for (int i = 0; i < 80; i++) {
        insert(hashTable, colors[i]);
    }
}

int main() {
    Node *hashTable[LIST_SIZE]; initDictionary(hashTable);
    populateHashTable(hashTable);

    printf("\n=== Hash Table ===\n");
    display(hashTable);

    Color delColor[5] = {{"Black", {0, 0, 0}},
                        {"Red", {255, 0, 0}},
                        {"Blue", {0, 32, 255}},
                        {"Orange", {255, 165, 0}},
                        {"White", {255, 255, 255}}
    };

    for (int i = 0; i < 5; i++) {
        deleteYo(hashTable, delColor[i]);
    }
    printf("\n=== Hash Table after Deletion ===\n");
    display(hashTable);

    Color searchColor = {"Green", {0, 128, 0}};
    search(hashTable, searchColor);

    return 0;
}
