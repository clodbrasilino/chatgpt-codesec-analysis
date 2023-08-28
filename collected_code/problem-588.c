#include <stdio.h>

int findDifference(int arr[], int size) {
    int i, min, max;
    min = max = arr[0];
    for (i = 1; i < size; i++) {
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
    int arr[] = {5, 8, 2, 10, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    int difference = findDifference(arr, size);
    printf("The difference between the largest and smallest value is: %d\n", difference);
    return 0;
}