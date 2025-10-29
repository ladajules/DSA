#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int studentID;
    char name[50];
    float gpa;
    char major[30];
    struct Student *next;
} Student;

typedef struct HashTable {
    Student **table;
    int size;
    int count;
} HashTable;

HashTable *createHashTable(int size) {
    HashTable *nt = malloc(sizeof(HashTable));
    nt->table = malloc(sizeof(Student) * size);
    for (int i = 0; i < size; i++) {
        nt->table[i] = NULL;
    }
    nt->size = size;
    nt->count = 0;
    return nt;
}

int hashFunction(int studentID, int tableSize) {
    return studentID % tableSize;
}

void insertStudent(HashTable *ht, int id, char name[], float gpa, char *major) {
    if (ht->count == ht->size) {
        printf("Full.\n");
        return;
    }

    int index = hashFunction(id, ht->size);

    Student *newStud = malloc(sizeof(Student));
    newStud->studentID = id;
    strcpy(newStud->name, name);
    newStud->gpa = gpa;
    strcpy(newStud->major, major);
    newStud->next = NULL;

    if (ht->table[index] == NULL) {
        ht->table[index] = newStud;
        ht->count++;
    } else {
        Student *temp = ht->table[index];

        while (temp->next && newStud->studentID > temp->next->studentID) {
            temp = temp->next;
        }

        if (temp->next == NULL) {
            temp->next = newStud;
        } else {
            newStud->next = temp->next;
            temp->next = newStud;
        }
        ht->count++;
    }
}

Student *searchStudent(HashTable ht, int id) {
    int index = hashFunction(id, ht.size);

    if (ht.table[index] == NULL) {
        printf("Not found.\n");
        return NULL;
    } else {
        Student *temp = ht.table[index];
        while (temp) {
            if (temp->studentID == id) return temp;
            temp = temp->next;
        }

        return NULL;
    }
}

int deleteStudent(HashTable *ht, int id) {
    int index = hashFunction(id, ht->size);
    int ret;

    if (ht->table[index] == NULL) {
        return 0;
    }

    if (ht->table[index]->studentID == id) {
        Student *toDel = ht->table[index];
        ret = toDel->studentID;
        ht->table[index] = toDel->next;
        free(toDel);
        ht->count--;
        return ret;
    } else {
        Student *temp = ht->table[index];

        while (temp->next && temp->next->studentID != id) {
            temp = temp->next;
        }

        if (temp->next == NULL) {
            printf("Last node nas del function and wala nakitan.\n");
        } else {
            Student *toDel = temp->next;
            ret = toDel->studentID;
            temp->next = toDel->next;
            free(toDel);
            ht->count--;
            return ret;
        }
    }
    return 0;
}

void displayChain(HashTable ht, int index) {
    Student *temp = ht.table[index];
    while (temp) {
        printf("-> ID=%d, Name=%s, GPA=%.2f, Major=%s\n", temp->studentID, temp->name, temp->gpa, temp->major);
        temp = temp->next;
    }
}

float calculateLoadFactor(HashTable *ht) {
    return (float)ht->count / ht->size;
}

void displayStatistics(HashTable ht) {
    printf("Total students: %d\n", ht.count);
    printf("Table size: %d\n", ht.size);
    printf("Load factor: %.2f\n", calculateLoadFactor(&ht));
    printf("Empty slots: %d\n", ht.size - ht.count);
}

int main() {
    // printf("=== Test Case 1.1: Basic Operations ===\n\n");
    
    // // Create hash table with size 7
    // HashTable* ht = createHashTable(7);
    // printf("Created hash table with size: 7\n\n");
    
    // // Insert students
    // printf("Inserting students...\n");
    // insertStudent(ht, 1001, "Alice Johnson", 3.8, "Computer Science");
    // printf("Inserted: ID=1001, Name=Alice Johnson, GPA=3.8, Major=Computer Science\n");
    
    // insertStudent(ht, 1002, "Bob Smith", 3.5, "Mathematics");
    // printf("Inserted: ID=1002, Name=Bob Smith, GPA=3.5, Major=Mathematics\n");
    
    // insertStudent(ht, 1003, "Carol White", 3.9, "Physics");
    // printf("Inserted: ID=1003, Name=Carol White, GPA=3.9, Major=Physics\n\n");
    
    // // Search for existing student
    // printf("Searching for student ID=1002...\n");
    // Student* result = searchStudent(*ht, 1002);
    // if (result != NULL) {
    //     printf("Found: ID=%d, Name=%s, GPA=%.2f, Major=%s\n\n",
    //            result->studentID, result->name, result->gpa, result->major);
    // }
    
    // // Search for non-existent student
    // printf("Searching for student ID=9999...\n");
    // result = searchStudent(*ht, 9999);
    // if (result == NULL) {
    //     printf("Student not found\n\n");
    // }
    
    // // Display load factor
    // float loadFactor = calculateLoadFactor(ht);
    // printf("Current load factor: %.2f\n\n", loadFactor);
    
    // // Display statistics
    // printf("Table Statistics:\n");
    // displayStatistics(*ht);
    // //===============================================================================
    
    // //===============================================================================
    // printf("=== Test Case 1.2: Collision Handling ===\n\n");
    
    // HashTable* ht = createHashTable(7);
    // printf("Created hash table with size: 7\n\n");
    
    // // Insert students that will collide (all should hash to same index)
    // // Assuming IDs that differ by table size hash to same location
    // printf("Inserting students with IDs that will collide...\n");
    // insertStudent(ht, 1001, "Alice Johnson", 3.8, "Computer Science");
    // printf("Inserted: ID=1001 (hash=%d)\n", 1001 % 7);
    
    // insertStudent(ht, 1008, "Bob Smith", 3.5, "Mathematics");
    // printf("Inserted: ID=1008 (hash=%d)\n", 1008 % 7);
    
    // insertStudent(ht, 1015, "Carol White", 3.9, "Physics");
    // printf("Inserted: ID=1015 (hash=%d)\n", 1015 % 7);
    
    // insertStudent(ht, 1022, "David Brown", 3.7, "Chemistry");
    // printf("Inserted: ID=1022 (hash=%d)\n\n", 1022 % 7);
    
    // // Display the chain at index where they collided
    // int collisionIndex = 1001 % 7;
    // printf("Displaying chain at index %d:\n", collisionIndex);
    // displayChain(*ht, collisionIndex);
    // printf("\n");
    
    // // Search for students in the chain
    // printf("Searching for students in collision chain...\n");
    // Student* result = searchStudent(*ht, 1008);
    // if (result != NULL) {
    //     printf("Found: ID=%d, Name=%s\n", result->studentID, result->name);
    // }
    
    // result = searchStudent(*ht, 1015);
    // if (result != NULL) {
    //     printf("Found: ID=%d, Name=%s\n", result->studentID, result->name);
    // }
    
    // result = searchStudent(*ht, 1022);
    // if (result != NULL) {
    //     printf("Found: ID=%d, Name=%s\n\n", result->studentID, result->name);
    // }
    
    // // Display statistics
    // printf("Table Statistics:\n");
    // displayStatistics(*ht);
    //=========================================================================================

    //===============================================================================
    printf("=== Test Case 1.3: Deletion Operations ===\n\n");
    
    HashTable* ht = createHashTable(7);
    
    // Setup: Insert students with collisions
    printf("Setting up hash table with collision chain...\n");
    insertStudent(ht, 1001, "Alice Johnson", 3.8, "Computer Science");
    insertStudent(ht, 1008, "Bob Smith", 3.5, "Mathematics");
    insertStudent(ht, 1015, "Carol White", 3.9, "Physics");
    insertStudent(ht, 1022, "David Brown", 3.7, "Chemistry");
    printf("Inserted 4 students at index 0\n\n");
    
    // Display initial chain
    printf("Initial chain at index 0:\n");
    displayChain(*ht, 0);
    printf("\n");
    
    // Delete from middle of chain
    printf("Deleting student ID=1008 (middle of chain)...\n");
    int deleteResult = deleteStudent(ht, 1008);
    if (deleteResult) {
        printf("Successfully deleted ID=1008\n\n");
    }
    
    // Display chain after deletion
    printf("Chain after deletion:\n");
    displayChain(*ht, 0);
    printf("\n");
    
    // Verify deletion
    printf("Verifying deletion...\n");
    Student* result = searchStudent(*ht, 1008);
    printf("Search for ID=1008: %s\n", result == NULL ? "Not found (correct)" : "Found (error)");
    
    result = searchStudent(*ht, 1001);
    printf("Search for ID=1001: %s\n", result != NULL ? "Found (correct)" : "Not found (error)");
    
    result = searchStudent(*ht, 1015);
    printf("Search for ID=1015: %s\n", result != NULL ? "Found (correct)" : "Not found (error)");
    
    result = searchStudent(*ht, 1022);
    printf("Search for ID=1022: %s\n\n", result != NULL ? "Found (correct)" : "Not found (error)");
    
    // Delete from head of chain
    printf("Deleting student ID=1001 (head of chain)...\n");
    deleteResult = deleteStudent(ht, 1001);
    if (deleteResult) {
        printf("Successfully deleted ID=1001\n\n");
    }
    
    printf("Chain after deleting head:\n");
    displayChain(*ht, 0);
    printf("\n");
    
    // Delete from tail
    printf("Deleting student ID=1022 (tail of chain)...\n");
    deleteResult = deleteStudent(ht, 1022);
    if (deleteResult) {
        printf("Successfully deleted ID=1022\n\n");
    }
    
    printf("Chain after deleting tail:\n");
    displayChain(*ht, 0);
    printf("\n");
    
    // Try deleting non-existent student
    printf("Attempting to delete non-existent student ID=9999...\n");
    deleteResult = deleteStudent(ht, 9999);
    printf("Delete result: %s\n", deleteResult ? "Success (error)" : "Failed (correct)");

    return 0;
}