#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct {
    int id;
    char title[64];
    char content[255];
} Article;

typedef struct {
    Article data;
    int next;
} HeapSpace;

typedef struct {
    HeapSpace H[MAX];
    int avail;
} VHeap;

typedef int List;

void initVHeap(VHeap *v) {
    int i;
    for ( i = 0; i < MAX - 1; i++) {
        v->H[i].next = i + 1;
    }
    v->H[i].next = -1;
    v->avail = 0;
}

int allocSpace(VHeap *v) {
    int ret = v->avail;
    if (ret != -1) {
        v->avail = v->H[ret].next;
    }
    return ret;
}

void dealloc(VHeap *v, int index) {
    if (index != -1) {
        v->H[index].next = v->avail;
        v->avail = index;
    }
}

void insert(VHeap *v, List *L, int id, char title[], char content[]) {
    int newNode = allocSpace(v);
    if (newNode == -1) {
        printf("Memory allocation failed.\n");
        return;
    }
    v->H[newNode].data.id = 1001 + id;
    strcpy(v->H[newNode].data.title, title);
    strcpy(v->H[newNode].data.content, content);
    v->H[newNode].next = -1;

    if (*L == -1) {
        *L = newNode;
    } else {
        int temp;
        for ( temp = *L; v->H[temp].next != -1; temp = v->H[temp].next );
        v->H[temp].next = newNode;
    }
    printf("%d Added.\n", 1001 + id);
}

int delete(VHeap *v, List *L, int id) {
    int temp, prev;
    for ( temp = *L, prev = -1;  temp != -1 && v->H[temp].data.id != id; prev = temp, temp = v->H[temp].next );

    int ret;
    if (temp == -1) {
        printf("Not found.\n");
        ret = -1;
    } else if (prev == -1) {
        ret = v->H[temp].data.id;
        *L = v->H[temp].next;
        dealloc(v, temp);
    } else {
        ret = v->H[temp].data.id;
        v->H[prev].next = v->H[temp].next;
        dealloc(v, temp);
    }

    return ret;
}

void search(VHeap *v, List L, int id) {
    int temp;
    for ( temp = L;  temp != -1 && v->H[temp].data.id != id; temp = v->H[temp].next );

    if (temp == -1) {
        printf("Not found.\n");
    } else {
        printf("%d - %s %s\n", v->H[temp].data.id, v->H[temp].data.title, v->H[temp].data.content);
    }
}

void display(VHeap *v, List L) {
    int temp = L;
    while (temp != -1) {
        printf("%d - %s %s\n", v->H[temp].data.id, v->H[temp].data.title, v->H[temp].data.content);
        temp = v->H[temp].next;
    }
    printf("\n");
}

int countElements(VHeap *v, List L) {
    int temp = L;
    int count;
    for ( count = 0 ; temp != -1 ; count++, temp = v->H[temp].next);

    return count;
}

int main() {
    VHeap v; List L = -1;
    initVHeap(&v);

    int choice;
    while(1) {
        printf("\n1. Add article\n2. Search for an article\n3. Delete an article\n4. Display\n5. Exit\nChoose: "); scanf("%d", &choice);

        switch(choice) {
            case 1:
            char title[64], content[255];
            printf("Enter title: "); scanf(" %[^\n]s", title);
            printf("Enter content of the article: "); scanf(" %[^\n]s", content);
            int count = countElements(&v, L);
            insert(&v, &L, count, title, content);
            break;

            case 2:
            int idToSearch;
            printf("Enter id to search: "); scanf("%d", &idToSearch);
            search(&v, L, idToSearch);
            break;

            case 3:
            int idToDel;
            printf("Enter id to search: "); scanf("%d", &idToDel);
            printf("Article ID %d deleted.\n", delete(&v, &L, idToDel));
            break;

            case 4:
            printf("\n==== Knowledge Base ====\n");
            display(&v, L);
            break;

            case 5:
            printf("Exiting program..\n");
            return 1;
            break;

            default:
            printf("Invalid choice. Enter again\n\n");
        }
    }

    return 0;
}

/* GUIDE QUESTIONS
1. Write the function for inserting a new article.
    void insert(VHeap *v, List *L, int id, char title[], char content[]) {
        int newNode = allocSpace(v);
        if (newNode == -1) {
            printf("Memory allocation failed.\n");
            return;
        }
        v->H[newNode].data.id = 1001 + id;
        strcpy(v->H[newNode].data.title, title);
        strcpy(v->H[newNode].data.content, content);
        v->H[newNode].next = -1;

        if (*L == -1) {
            *L = newNode;
        } else {
            int temp;
            for ( temp = *L; v->H[temp].next != -1; temp = v->H[temp].next );
            v->H[temp].next = newNode;
        }
        printf("%d Added.\n", 1001 + id);
    }

2. Write the function for searching an article.
    void search(VHeap *v, List L, int id) {
        int temp;
        for ( temp = L;  temp != -1 && v->H[temp].data.id != id; temp = v->H[temp].next );
        if (temp == -1) printf("Not found.\n");
        else printf("%d - %s %s\n", v->H[temp].data.id, v->H[temp].data.title, v->H[temp].data.content);
    }

3. Write the function for deleting an article.
    int delete(VHeap *v, List *L, int id) {
        int temp, prev;
        for ( temp = *L, prev = -1;  temp != -1 && v->H[temp].data.id != id; prev = temp, temp = v->H[temp].next );

        int ret;
        if (temp == -1) {
            printf("Not found.\n");
            ret = -1;
        } else if (prev == -1) {
            ret = v->H[temp].data.id;
            *L = v->H[temp].next;
            dealloc(v, temp);
        } else {
            ret = v->H[temp].data.id;
            v->H[prev].next = v->H[temp].next;
            dealloc(v, temp);
        }

        return ret;
    }


*/

