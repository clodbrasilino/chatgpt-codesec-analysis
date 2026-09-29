#include <stdio.h>
#include <stdlib.h>

int find_smallest_frequency(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int smallest = array[0];
    int frequency = 1;

    for (size_t i = 1; i < size; i++) {
        if (array[i] < smallest) {
            smallest = array[i];
            frequency = 1;
        } else if (array[i] == smallest) {
            frequency++;
        }
    }

    return frequency;
}

int main(void) {
    int arr[] = {5, 2, 8, 2, 1, 4, 1, 1, 7};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int result = find_smallest_frequency(arr, n);

    printf("%d\n", result);

    return 0;
}