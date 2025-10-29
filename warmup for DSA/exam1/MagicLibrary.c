#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10

typedef struct {
    char bookTitle[25];
} Shelf;

typedef struct {
    Shelf books[MAX];
    int top;
} Stack;

void returnBook(Stack *s, char *bookTitle) {
    if (s->top == MAX - 1) {
        printf("Library is full.\n");
    } else {
        s->top++;
        strcpy(s->books[s->top].bookTitle, bookTitle);
    }
    printf("Added: %s\n", bookTitle);
}

void processNextBook(Stack *s) {
    char temp[25];
    if (s->top == -1) {
        printf("Library is empty.\n");
    } else {
        strcpy(temp, s->books[s->top].bookTitle);
        s->top--;
    }
    printf("Processed: %s\n", temp);
}

void peekTopBook(Stack *s) {
    printf("Top book: %s\n", s->books[s->top].bookTitle);
}

int findCursedBooks(Stack s) {
    Stack temp = s;
    int count = 0;
    while (temp.top != -1) {
        if (strncmp("Dark", temp.books[temp.top].bookTitle, strlen("Dark")) == 0) {
            count++;
        } 
        temp.top--;
    }
    return count;
}
 
int main() {
    Stack s; 
    s.top = -1;

    returnBook(&s, "Potions for Beginners");
    returnBook(&s, "Dark Arts Revealed");
    returnBook(&s, "Herbology Guide");
    returnBook(&s, "Dark Magic Secrets");
    peekTopBook(&s);
    printf("Cursed books found: %d\n", findCursedBooks(s));
    processNextBook(&s);
    processNextBook(&s);
    peekTopBook(&s);

    return 0;
}