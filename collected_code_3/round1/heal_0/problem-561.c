#include <stdio.h>

#define SIZE 5

void assign_pairs(int arr1[], int arr2[], int arr3[][2], int n) {
    for(int i = 0; i < n; i++) {
        arr3[i][0] = arr1[i];
        arr3[i][1] = arr2[i];
    }
}

int main() {
    int arr1[SIZE] = {1, 2, 3, 4, 5};
    int arr2[SIZE] = {6, 7, 8, 9, 10};
    int arr3[SIZE][2];

    assign_pairs(arr1, arr2, arr3, SIZE);

    for(int i = 0; i < SIZE; i++) {
        printf("(%d, %d)\n", arr3[i][0], arr3[i][1]);
    }

    return 0;
}