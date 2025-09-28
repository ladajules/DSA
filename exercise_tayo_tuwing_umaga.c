#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int *evenNumbers (int *arr, int n) {
    int *result = (int *)malloc((n + 1) * sizeof(int));
    if (!result) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    int j = 0, i;
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            result[j++] = arr[i];
        }
    }
    result[j] = -1;

    result = realloc(result, (j + 1) * sizeof(int));
    if (!result) {
        printf("Memory reallocation failed!\n");
        exit(1);
    }

    return result;
}

void printArray(int *arr) {
    if (arr[0] == -1) {
        printf("No even numbers.\n");
        return;
    }

    int i = 0;
    printf("The array with only even numbers: {");
    while (arr[i] != -1) {
        printf("%d, ", arr[i]);
        i++;
    }
    printf("%d}", arr[i]);
}

int main() {
    // Test Case 1
    printf("Test Case 1:\n");
    int array1[MAX] = {1, 5, 7, 9, 11};

    int *result1 = evenNumbers(array1, MAX);
    printArray(result1);

    printf("\n");

    // Test Case 2
    printf("Test Case 2:\n");
    int array2[MAX] = {2, 4, 16, 28, 40};

    int *result2 = evenNumbers(array2, MAX);
    printArray(result2);

    return 0;
}