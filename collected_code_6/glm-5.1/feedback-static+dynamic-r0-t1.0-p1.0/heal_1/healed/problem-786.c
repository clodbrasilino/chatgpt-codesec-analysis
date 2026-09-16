#include <stdio.h>
#include <stdlib.h>

size_t find_insertion_point(const int *array, size_t size, int value) {
    if (array == NULL) {
        return 0;
    }

    size_t low = 0;
    size_t high = size;

    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (array[mid] < value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}

int main(void) {
    int arr[] = {1, 3, 3, 5, 7, 9};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    size_t idx = find_insertion_point(arr, size, 4);
    printf("%zu\n", idx);

    idx = find_insertion_point(arr, size, 3);
    printf("%zu\n", idx);

    idx = find_insertion_point(arr, size, 0);
    printf("%zu\n", idx);

    idx = find_insertion_point(arr, size, 10);
    printf("%zu\n", idx);

    idx = find_insertion_point(NULL, size, 5);
    printf("%zu\n", idx);

    return 0;
}