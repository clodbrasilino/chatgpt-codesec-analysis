#include<stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void findLargestNumber(const int arr[], const int size) {
    int sortedArr[size];
    for (int i = 0; i < size; i++) sortedArr[i] = arr[i];

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (sortedArr[i] < sortedArr[j]) {
                swap(&sortedArr[i], &sortedArr[j]);
            }
        }
    }

    printf("Largest number: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", sortedArr[i]);
    }
}

int main() {
    const int arr[] = {9, 3, 7, 6, 1};
    const int size = sizeof(arr) / sizeof(arr[0]);

    findLargestNumber(arr, size);

    return 0;
}