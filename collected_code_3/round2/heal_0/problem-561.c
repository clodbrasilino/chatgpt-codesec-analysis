#include <stdio.h>

#define SIZE 5

void assignPairs(int arr1[], int arr2[], int n) {
    for(int i = 0; i < n; i++) {
        arr1[i] = arr2[i];
    }
}

int main() {
    int arr1[SIZE] = {1, 2, 3, 4, 5};
    int arr2[SIZE] = {6, 7, 8, 9, 10};

    assignPairs(arr1, arr2, SIZE);

    for(int i = 0; i < SIZE; i++) {
        printf("%d ", arr1[i]);
    }

    return 0;
}