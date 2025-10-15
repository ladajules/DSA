#include <stdio.h>
#include <math.h>

int getParent(int i) {
    return (i - 1) / 2;
}

int getLeftChild(int i) {
    return (2 * i) + 1;
}

int getRightChild(int i ) {
    return (2 * i) + 2;
}

void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void heapifyUp(int *bheap, int i) {
    if (i == 0) return; // in highest value alr

    int parent = getParent(i);

    if (bheap[i] > bheap[parent]) {
        swap(bheap[i], parent);

        heapifyUp(bheap, parent); // recursive
    }
}

void heapifyDown(int *bheap, int i) {
    //
}

void insert(int *bheap, int *size, int value) {
    bheap[*size] = value;
    heapifyUp(bheap, *size);
    (*size)++;
}

int main() {
    

    return 0;
}