#include <stdio.h>
#include <limits.h>

int find_difference(const int arr[], size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    int largest = arr[0];
    int smallest = arr[0];

    for (size_t i = 1; i < size; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }

    return largest - smallest;
}

int main(void) {
    int arr[] = {10, 5, 8, 20, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result = find_difference(arr, size);

    if (result != -1) {
        printf("Difference: %d\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}