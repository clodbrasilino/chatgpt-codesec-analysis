#include <stddef.h>

size_t lower_bound_insertion_point(const int *array, size_t size, int value) {
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

#include <stdio.h>

int main(void) {
    int sorted_array[] = {1, 3, 5, 7, 9, 11};
    size_t size = sizeof(sorted_array) / sizeof(sorted_array[0]);

    int values_to_insert[] = {0, 1, 2, 5, 8, 11, 12};
    size_t num_tests = sizeof(values_to_insert) / sizeof(values_to_insert[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        size_t pos = lower_bound_insertion_point(sorted_array, size, values_to_insert[i]);
        printf("Insert %d at index %zu\n", values_to_insert[i], pos);
    }

    return 0;
}