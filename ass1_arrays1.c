#include <stdio.h>

int isUnique(int arr[], int size) {
    int i, j;
    int flag = 1;

    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size - 1; j++) {
            if (arr[i] == arr[j]) {
                flag = 0;
            }
        }
    }

    return flag;
}

int main() {
    // Test Case 1:
    int A[6] = {7, 6, 9, 4, 7, 3};

    if (isUnique(A, sizeof(A) / sizeof(A[0])) == 1) {
        printf("Integers in the array are unique.\n");
    } else {
        printf("Integers in the array are not unique.\n");
    }

    // Test Case 2:
    int B[6] = {4, 9, 6, 3, 7, 8};

    if (isUnique(B, sizeof(B) / sizeof(B[0])) == 1) {
        printf("Integers in the array are unique.\n");
    } else {
        printf("Integers in the array are not unique.\n");
    }


    return 0;
}