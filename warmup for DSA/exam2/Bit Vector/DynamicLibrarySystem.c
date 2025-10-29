#include <stdio.h>
#include <stdlib.h>

typedef struct BookNode {
    int isbn;
    char title[100];
    char author[50];
    int year;
    struct BookNode *next;
} BookNode;

typedef struct {
    BookNode *head;
    int count;
} Bucket;

typedef struct {
    Bucket *buckets;
    int N; // current number of buckets
    int level; // current level ( N = level^2 * N0 )
    int split; // next bucket to split ( 0 to N-1 )
    int N0; // initial number of buckets
    int totalBooks;
} LinearHashTable;

int main() {

    return 0;
}