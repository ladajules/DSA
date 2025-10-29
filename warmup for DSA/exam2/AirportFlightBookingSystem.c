#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { 
    EMPTY,
    OCCUPIED,
    DELETED
} SlotStatus;

typedef struct Flight {
    char flightCode[7];
    char destination[50];
    int availableSeats;
    float price;
    SlotStatus status;
} Flight;

typedef struct {
    Flight *table;
    int size;
    int occupiedCount;
    int deletedCount;
} FlightHashTable;

FlightHashTable *createFlightTable(int size) {
    FlightHashTable *nt = malloc(sizeof(FlightHashTable));
    nt->table = malloc(sizeof(Flight) * size);
    for (int i = 0; i < size; i++) {
        nt->table[i].status = EMPTY;
    }
    nt->size = size;
    nt->occupiedCount = nt->deletedCount = 0;
    
    return nt;
}

int hashFlightCode(char flightCode[], int tableSize) {
    int sum = 0;
    for (int i = 0; flightCode[i] != '\0'; i++) {
        sum += flightCode[i] * (i + 1);
    }
    return sum % tableSize;
}

int insertFlight(FlightHashTable *ht, char code[], char *dest, int seats, float price) {
    if (ht->size == ht->occupiedCount) { printf("Full na.\n"); return 0; }
    int index = hashFlightCode(code, ht->size);

    Flight nt;
    strcpy(nt.flightCode, code);
    strcpy(nt.destination, dest);
    nt.availableSeats = seats;
    nt.price = price;

    if (ht->table[index].status == EMPTY || ht->table[index].status == DELETED) {
        ht->table[index] = nt;
        ht->table[index].status = OCCUPIED;
        ht->occupiedCount++;
        return 1;
    } else {
        for (; ht->table[index].status != EMPTY; index = (index + 1) % ht->size);

        ht->table[index] = nt;
        ht->table[index].status = OCCUPIED;
        ht->occupiedCount++;
        return 1;
    }
    return 0;
}

Flight *searchFlight(FlightHashTable ht, char flightCode[]) {
    int initIndex = hashFlightCode(flightCode, ht.size);
    int newIndex = initIndex;

    do {
        if (ht.table[newIndex].status == EMPTY) return NULL;

        if (ht.table[newIndex].status == OCCUPIED && strcmp(ht.table[newIndex].flightCode, flightCode) == 0) return &ht.table[newIndex];

        newIndex = (newIndex + 1) % ht.size;
    } while (newIndex != initIndex);

    return NULL;
}

int deleteFlight(FlightHashTable *ht, char flightCode[]) {
    int index = hashFlightCode(flightCode, ht->size);

    if (ht->table[index].status == OCCUPIED) {
        ht->table[index].status = DELETED;
        ht->occupiedCount--;
        ht->deletedCount++;
        return 1;
    }
    return 0;
}

void updateSeats(FlightHashTable ht, char flightCode[], int newSeats) {
    int index = hashFlightCode(flightCode, ht.size);
    ht.table[index].availableSeats = newSeats;
}

int needsRehashing(FlightHashTable ht) {
    if (((float)ht.occupiedCount / ht.size) > 0.7) {
        return 1;
    }   
    return 0;
}

FlightHashTable *rehash(FlightHashTable ht) {
    FlightHashTable *nt = createFlightTable(ht.size * 2); 
    for (int i = 0; i < ht.size; i++) {
        if (ht.table[i].status == OCCUPIED) {
            insertFlight(nt, ht.table[i].flightCode, ht.table[i].destination, ht.table[i].availableSeats, ht.table[i].price);
        }
    }
    return nt;
}

int main() {
    // printf("=== Test Case 2.1: Basic Linear Probing ===\n\n");
    
    // FlightHashTable* ht = createFlightTable(11);
    // printf("Created flight hash table with size: 11\n\n");
    
    // // Insert flights
    // printf("Inserting flights...\n");
    // int result = insertFlight(ht, "AA1234", "New York", 150, 299.99);
    // printf("Insert AA1234: %s (index=%d)\n", 
    //        result ? "Success" : "Failed", 
    //        hashFlightCode("AA1234", 11));
    
    // result = insertFlight(ht, "BB5678", "London", 200, 599.99);
    // printf("Insert BB5678: %s (index=%d)\n", 
    //        result ? "Success" : "Failed",
    //        hashFlightCode("BB5678", 11));
    
    // result = insertFlight(ht, "CC9012", "Tokyo", 180, 899.99);
    // printf("Insert CC9012: %s (index=%d)\n\n", 
    //        result ? "Success" : "Failed",
    //        hashFlightCode("CC9012", 11));
    
    // // Search for flights
    // printf("Searching for flights...\n");
    // Flight* flight = searchFlight(*ht, "BB5678");
    // if (flight != NULL) {
    //     printf("Found: %s -> %s, Seats=%d, Price=$%.2f\n\n",
    //            flight->flightCode, flight->destination,
    //            flight->availableSeats, flight->price);
    // }
    
    // // Display table status
    // printf("Table Status:\n");
    // printf("Occupied slots: %d\n", ht->occupiedCount);
    // printf("Deleted slots: %d\n", ht->deletedCount);
    // printf("Load factor: %.2f\n", (float)ht->occupiedCount / ht->size);
    // ========================================================================================

    //========================================================================================
    // printf("=== Test Case 2.2: Linear Probing Collisions ===\n\n");
    
    // FlightHashTable* ht = createFlightTable(11);
    // printf("Created flight hash table with size: 11\n\n");
    
    // // Insert flights that will collide
    // printf("Inserting flights with collisions...\n");
    
    // insertFlight(ht, "FL0001", "Paris", 150, 450.00);
    // int home1 = hashFlightCode("FL0001", 11);
    // printf("Inserted FL0001 at home position: %d\n", home1);
    
    // insertFlight(ht, "FL0012", "Rome", 160, 480.00);
    // int home2 = hashFlightCode("FL0012", 11);
    // printf("Inserted FL0012 (home=%d, ", home2);
    // // Find actual position by searching
    // for (int i = 0; i < 11; i++) {
    //     if (ht->table[i].status == OCCUPIED && 
    //         strcmp(ht->table[i].flightCode, "FL0012") == 0) {
    //         printf("actual=%d, probes=%d)\n", i, (i - home2 + 11) % 11 + 1);
    //         break;
    //     }
    // }
    
    // insertFlight(ht, "FL0023", "Berlin", 170, 500.00);
    // int home3 = hashFlightCode("FL0023", 11);
    // printf("Inserted FL0023 (home=%d, ", home3);
    // for (int i = 0; i < 11; i++) {
    //     if (ht->table[i].status == OCCUPIED && 
    //         strcmp(ht->table[i].flightCode, "FL0023") == 0) {
    //         printf("actual=%d, probes=%d)\n\n", i, (i - home3 + 11) % 11 + 1);
    //         break;
    //     }
    // }
    
    // // Display table layout
    // printf("Table layout:\n");
    // printf("Index | Status    | Flight Code | Destination\n");
    // printf("------|-----------|-------------|-------------\n");
    // for (int i = 0; i < 11; i++) {
    //     char* status;
    //     if (ht->table[i].status == EMPTY) status = "EMPTY";
    //     else if (ht->table[i].status == OCCUPIED) status = "OCCUPIED";
    //     else status = "DELETED";
        
    //     if (ht->table[i].status == OCCUPIED) {
    //         printf("  %2d  | %-9s | %-11s | %s\n", i, status,
    //                ht->table[i].flightCode, ht->table[i].destination);
    //     } else {
    //         printf("  %2d  | %-9s | -           | -\n", i, status);
    //     }
    // }
    // printf("\n");
    
    // // Search with probe counting
    // printf("Searching for FL0023...\n");
    // Flight* flight = searchFlight(*ht, "FL0023");
    // if (flight != NULL) {
    //     printf("Found: %s -> %s\n", flight->flightCode, flight->destination);
    // }
    
    // printf("\nObservation: Primary clustering visible - consecutive occupied slots\n");
    // ========================================================================================

    // ========================================================================================
    printf("=== Test Case 2.3: Lazy Deletion ===\n\n");
    
    FlightHashTable* ht = createFlightTable(11);
    
    // Setup: Insert flights with collisions (all hash to index 3)
    printf("Setup: Inserting flights...\n");
    insertFlight(ht, "FL0001", "Paris", 150, 450.00);
    insertFlight(ht, "FL0012", "Rome", 160, 480.00);
    insertFlight(ht, "FL0023", "Berlin", 170, 500.00);
    insertFlight(ht, "FL0034", "Madrid", 180, 520.00);
    printf("Inserted 4 flights\n\n");
    
    // Display initial table
    printf("Initial table:\n");
    for (int i = 0; i < 11; i++) {
        if (ht->table[i].status == OCCUPIED) {
            printf("Index %2d: %s -> %s\n", i, 
                   ht->table[i].flightCode, ht->table[i].destination);
        }
    }
    printf("\n");
    
    // Delete a flight in the middle of probe sequence
    printf("Deleting FL0012...\n");
    int delResult = deleteFlight(ht, "FL0012");
    printf("Delete result: %s\n\n", delResult ? "Success" : "Failed");
    
    // Display table after deletion
    printf("Table after deletion:\n");
    for (int i = 0; i < 11; i++) {
        if (ht->table[i].status == OCCUPIED) {
            printf("Index %2d: %s -> %s\n", i,
                   ht->table[i].flightCode, ht->table[i].destination);
        } else if (ht->table[i].status == DELETED) {
            printf("Index %2d: [DELETED]\n", i);
        }
    }
    printf("\n");
    
    // Search for flight after the deleted one
    printf("Searching for FL0023 (should pass through DELETED slot)...\n");
    Flight* flight = searchFlight(*ht, "FL0023");
    if (flight != NULL) {
        printf("Found: %s -> %s (correct - search continued through DELETED)\n\n",
               flight->flightCode, flight->destination);
    }
    
    // Verify deleted flight is not found
    printf("Searching for deleted flight FL0012...\n");
    flight = searchFlight(*ht, "FL0012");
    printf("Result: %s\n\n", flight == NULL ? "Not found (correct)" : "Found (error)");
    
    // Insert new flight - should reuse DELETED slot
    printf("Inserting new flight FL9999...\n");
    insertFlight(ht, "FL9999", "Athens", 190, 540.00);
    
    printf("\nTable after new insertion:\n");
    for (int i = 0; i < 11; i++) {
        if (ht->table[i].status == OCCUPIED) {
            printf("Index %2d: %s -> %s\n", i,
                   ht->table[i].flightCode, ht->table[i].destination);
        } else if (ht->table[i].status == DELETED) {
            printf("Index %2d: [DELETED]\n", i);
        }
    }
    
    printf("\nTable statistics:\n");
    printf("Occupied: %d, Deleted: %d, Load factor: %.2f\n",
           ht->occupiedCount, ht->deletedCount,
           (float)ht->occupiedCount / ht->size);

    return 0;
}