#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int fragmentID;
    struct node *next;
} Fragment;

typedef struct {
    Fragment *front, *rear;
} Chain;

void init(Chain *c) {
    c->front = c->rear = NULL;
}

int front(Chain *c) {
    return c->front->fragmentID;
}

void enqueue(Chain *c, int fragmentID) {
    Fragment *newNode = malloc(sizeof(Fragment));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->fragmentID = fragmentID;
    newNode->next = NULL;

    if (c->front == NULL) {
        c->front = c->rear = newNode;
    } else {
        c->rear->next = newNode;
        c->rear = newNode;
    }
}

void enqueueCycle(Chain *c, int fragmentID) {
    Fragment *newNode = malloc(sizeof(Fragment));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->fragmentID = fragmentID;

    if (c->front == NULL) {
        c->front = c->rear = newNode;
    } else {
        c->rear->next = newNode;
        c->rear = newNode;
    }
    newNode->next = c->front;
}

void dequeue(Chain *c) {
    if (c->front == NULL) {
        printf("empty.\n");
    } else {
        Fragment *toDel = c->front;
        c->front = toDel->next;
        free(toDel);
    }
}

bool hasCycle(Chain c) {
    bool flag = false;
    if (c.front == NULL)  {
        flag = false;
    } else {
        Fragment *tortoise = c.front, *hare = c.front;

        while (hare != NULL && hare->next != NULL) {
            tortoise = tortoise->next;
            hare = hare->next->next;

            if (tortoise == hare) flag = true;
        }
    }
    return flag;
}

int countFragments(Chain *c) {
    int count = 0;
    if (c->front == NULL || hasCycle(*c)) {
        count = -1;
    } else {
        Chain tempChain; init(&tempChain);

        while (c->front != NULL) {
            count++;
            enqueue(&tempChain, front(c));
            dequeue(c);
        }

        while (tempChain.front != NULL) {
            enqueue(c, front(&tempChain));
            dequeue(&tempChain);
        }
    }
    return count;
}

void display(Chain *c) {
    if (c->front == NULL) {
        printf("empty.\n");
    } else {
        if (hasCycle(*c)) {
            printf("[CYCLE DETECTED]");
        } else {
            Chain tempChain; init(&tempChain);

            while (c->front != NULL) {
                printf("%d -> ", front(c));
                enqueue(&tempChain, front(c));
                dequeue(c);
            }
            printf("NULL");

            while (tempChain.front != NULL) {
                enqueue(c, front(&tempChain));
                dequeue(&tempChain);
            }
        }
    }
    printf("\n");
}

int main() {
    Chain c[3]; 
    for (int i = 0; i < 3; i++) {
        init(&c[i]);
    }

    // Chain 1
    enqueue(&c[0], 101);
    enqueue(&c[0], 205);
    enqueue(&c[0], 333);

    // Chain 2
    enqueue(&c[1], 777);

    // Chain 3
    enqueue(&c[2], 444);
    enqueue(&c[2], 555);
    enqueueCycle(&c[2], 666);

    for (int i = 0; i < 3; i++) {
        printf("Chain %d Analysis:\n", i + 1);
        printf("- Anchor Point: Fragment %d\n", front(&c[i]));
        printf("Fragments: "); display(&c[i]);
        printf("- Status: ");

        if (!hasCycle(c[i])) printf("ACCESSIBLE ");
        else printf("PARTIALLY ACCESSIBLE ");
        
        if(countFragments(&c[i]) == -1) printf("(infinite loop detected - knowledge trapped)\n\n");
        else printf("(%d fragment/s reachable)\n\n", countFragments(&c[i]));
    }

    return 0;
}