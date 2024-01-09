#include<stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void findLargestNumber(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] < arr[j]) {
                swap(&arr[i], &arr[j]);
            }
        }
    }

    printf("Largest number: ");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
    }
}

int main() {
    int arr[] = {9, 3, 7, 6, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    findLargestNumber(arr, size);

    return 0;
}