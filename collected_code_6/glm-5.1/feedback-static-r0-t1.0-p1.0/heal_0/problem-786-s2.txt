#include <stdio.h>
#include <stdlib.h>

size_t find_right_insertion_point(const int *array, size_t length, int value) {
    if (array == NULL) {
        return 0;
    }

    size_t low = 0;
    size_t high = length;

    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (array[mid] <= value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}

int main(void) {
    int arr[] = {1, 2, 2, 3, 5, 6, 8, 9};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    int values_to_insert[] = {0, 2, 4, 9, 10};
    size_t num_values = sizeof(values_to_insert) / sizeof(values_to_insert[0]);

    for (size_t i = 0; i < num_values; ++i) {
        size_t pos = find_right_insertion_point(arr, len, values_to_insert[i]);
        printf("Value %d: Insertion point = %zu\n", values_to_insert[i], pos);
    }

    size_t null_pos = find_right_insertion_point(NULL, 0, 5);
    printf("NULL array test: Insertion point = %zu\n", null_pos);

    return 0;
}