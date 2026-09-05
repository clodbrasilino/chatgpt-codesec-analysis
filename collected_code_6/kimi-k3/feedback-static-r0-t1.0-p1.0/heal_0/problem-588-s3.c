#include <stdio.h>
#include <limits.h>

int find_difference(const int arr[], size_t size, int *result) {
    if (arr == NULL || result == NULL || size == 0) {
        return -1;
    }

    int min = arr[0];
    int max = arr[0];

    for (size_t i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    *result = max - min;
    return 0;
}

int main(void) {
    int arr[] = {10, 5, 20, 8, 15};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int difference;

    if (find_difference(arr, size, &difference) == 0) {
        printf("Difference: %d\n", difference);
    } else {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }

    return 0;
}