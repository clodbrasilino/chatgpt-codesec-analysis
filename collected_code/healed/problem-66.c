#include <stdio.h>

int countPositiveNumbers(const int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, -2, 3, -4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int positiveCount = countPositiveNumbers(arr, size);
    printf("Number of positive numbers in the list: %d\n", positiveCount);
    return 0;
}