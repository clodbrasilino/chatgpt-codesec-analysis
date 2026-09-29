#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static size_t find_right_insertion_point(const int *arr, size_t length, int value)
{
    size_t low = 0;
    size_t high = length;

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
    int sorted_values[] = {1, 3, 3, 5, 7, 9, 11};
    size_t length = sizeof(sorted_values) / sizeof(sorted_values[0]);
    int targets[] = {0, 3, 6, 11, 15};
    size_t target_count = sizeof(targets) / sizeof(targets[0]);
    size_t i;

    for (i = 0; i < target_count; i++) {
        size_t pos = find_right_insertion_point(sorted_values, length, targets[i]);
        if (printf("Value %d -> insertion index %zu\n", targets[i], pos) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}