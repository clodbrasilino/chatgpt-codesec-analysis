#include <stdio.h>
#include <limits.h>

int findDifference(const int *arr, int size) {
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i = 0; i < size; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max - min;
}

int main() {
    int arr[] = {3, 1, 8, -2, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int difference = findDifference(arr, size);
    printf("Difference: %d\n", difference);
    return 0;
}