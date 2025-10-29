#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long sku;
    char productName[100];
    float price;
    int stockQuantity;
    int isOccupied;
} Product;

typedef struct {
    Product *table;
    int size;
    int numProducts;
} ProductHashTable;

ProductHashTable *initProductTable(int size) {
    ProductHashTable *nt = malloc(sizeof(ProductHashTable));
    nt->table = malloc(sizeof(Product) * size);
    for (int i = 0; i < size; i++) {
        nt->table[i].isOccupied = 0;
    }
    nt->size = size;
    nt->numProducts = 0;
    return nt;
}

int hashSKU(long long sku, int tableSize) {
    return sku % tableSize;
}

int quadraticProbe(int homeIndex, int attempt, int tableSize) {
    return (homeIndex + (attempt * attempt)) % tableSize;
}

void insertProduct(ProductHashTable *ht, long long sku, char name[], float price, int stock) {
    int homeIndex = hashSKU(sku, ht->size);

    Product newProd;
    newProd.sku = sku;
    strcpy(newProd.productName, name);
    newProd.price = price;
    newProd.stockQuantity = stock;
    newProd.isOccupied = 1;

    if (ht->table[homeIndex].isOccupied == 0) {
        ht->table[homeIndex] = newProd;
        ht->numProducts++;
    } else {
        int index;
        for (int i = 1; i < ht->size; i++) {
            index = quadraticProbe(homeIndex, i, ht->size);

            if (ht->table[index].isOccupied == 0 || ht->table[index].isOccupied == -1) {
                ht->table[index] = newProd;
                ht->numProducts++;
                break;
            }
        }
    }
}

Product *findProduct(ProductHashTable ht, long long sku) {
    int homeIndex = hashSKU(sku, ht.size);

    if (ht.table[homeIndex].isOccupied == 0) return NULL;

    if (ht.table[homeIndex].sku == sku) {
        return &ht.table[homeIndex];
    } else {
        int index;
        for (int i = 1; i < ht.size; i++) {
            index = quadraticProbe(homeIndex, i,ht.size);

            if (ht.table[index].isOccupied == 0) return NULL;
            if (ht.table[index].sku == sku) return &ht.table[index];
        }
    }
    return NULL;
}

void removeProduct(ProductHashTable *ht, long long sku) {
    int homeIndex = hashSKU(sku, ht->size);

    if (ht->table[homeIndex].sku == sku) {
        ht->table[homeIndex].isOccupied = -1;
    } else {
        int index;
        for (int i = 1; i < ht->size; i++) {
            index = quadraticProbe(homeIndex, i, ht->size);

            if (ht->table[index].isOccupied == 0) return;
            if (ht->table[index].sku == sku) ht->table[index].isOccupied = -1;
        }
    }
}

int main() {
    printf("=== Test Case 3.1: Quadratic Probing ===\n\n");
    
    ProductHashTable* ht = initProductTable(11);
    printf("Created product hash table with size: 11 (prime)\n\n");
    
    // Insert products
    printf("Inserting products...\n");
    insertProduct(ht, 1234567890, "Laptop", 999.99, 50);
    printf("Inserted SKU=1234567890 (hash=%d)\n", hashSKU(1234567890, 11));
    
    insertProduct(ht, 1234567901, "Mouse", 29.99, 200);
    printf("Inserted SKU=1234567901 (hash=%d)\n", hashSKU(1234567901, 11));
    
    insertProduct(ht, 1234567912, "Keyboard", 79.99, 150);
    printf("Inserted SKU=1234567912 (hash=%d)\n\n", hashSKU(1234567912, 11));
    
    // Search
    printf("Searching for SKU=1234567901...\n");
    Product* product = findProduct(*ht, 1234567901);
    if (product != NULL) {
        printf("Found: %s - $%.2f (Stock: %d)\n\n",
               product->productName, product->price, product->stockQuantity);
    }
    
    printf("Table Status:\n");
    printf("Products: %d, Load factor: %.2f\n",
           ht->numProducts, (float)ht->numProducts / ht->size);

    return 0;
}