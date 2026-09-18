#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int* newArray(int arr[], int n, int* length) {
    int* newArray = (int*)malloc(n * sizeof(int));
    int j = 0;

    if (newArray == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i]==arr[j])
                count++;
        }
        if (count < 3) {
            newArray[j++] = arr[i];
        }
    }
    *length = j;

    newArray = (int*)realloc(newArray, j * sizeof(int));
    /* Possible weaknesses found:
     *  leak of 'newArray' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return newArray;
}

void printArray(int arr[], int m) {
    for (int i = 0; i < m; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int data[SIZE];
    int length = SIZE;

    // Fill array
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % (SIZE / 2); // Random numbers;
    }

    printArray(data, SIZE);

    int* newData = newArray(data, SIZE, &length);
    if (newData != NULL) {
        printArray(newData, length);
        free(newData);
    }

    return 0;
}