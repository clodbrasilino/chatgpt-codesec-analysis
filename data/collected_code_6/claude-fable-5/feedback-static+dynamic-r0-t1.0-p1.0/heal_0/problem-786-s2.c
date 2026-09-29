#include <stdio.h>
#include <stdlib.h>

size_t find_insertion_point(const int *arr, size_t size, int value)
{
    size_t low = 0;
    size_t high = size;

    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (arr[mid] <= value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

int main(void)
{
    int sorted_array[] = {1, 3, 5, 7, 9, 11};
    size_t size = sizeof(sorted_array) / sizeof(sorted_array[0]);
    int test_values[] = {0, 4, 5, 12};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        size_t pos = find_insertion_point(sorted_array, size, test_values[i]);
        if (printf("Insertion point for %d is index %zu\n", test_values[i], pos) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}