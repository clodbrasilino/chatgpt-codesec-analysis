#include <stdio.h>

int findLargestPositiveNumber(const int arr[], int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int arr[] = {5, -8, 12, -3, 9, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int largestPositiveNumber = findLargestPositiveNumber(arr, size);
    printf("Largest positive number: %d", largestPositiveNumber);
    return 0;
}