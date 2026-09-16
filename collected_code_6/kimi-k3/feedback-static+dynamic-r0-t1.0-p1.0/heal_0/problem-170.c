#include <stdio.h>
#include <stdlib.h>

int sum_range(int *arr, int size, int start, int end) {
    if (arr == NULL || start < 0 || end >= size || start > end) {
        return -1;
    }

    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int start = 2;
    int end = 5;

    int result = sum_range(arr, size, start, end);
    if (result != -1) {
        printf("Sum of elements between index %d and %d: %d\n", start, end, result);
    } else {
        printf("Invalid range or array.\n");
    }

    return 0;
}