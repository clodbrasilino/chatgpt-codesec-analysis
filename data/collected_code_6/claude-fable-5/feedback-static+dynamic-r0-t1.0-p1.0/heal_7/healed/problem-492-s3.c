#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

bool binary_search(const int *arr, size_t size, int target, size_t *index)
{
    size_t low;
    size_t high;

    if (arr == NULL || index == NULL || size == 0U || size > (size_t)INT_MAX) {
        return false;
    }

    low = 0U;
    high = size;

    while (low < high) {
        size_t mid = low + ((high - low) / 2U);

        if (arr[mid] == target) {
            *index = mid;
            return true;
        }

        if (arr[mid] < target) {
            low = mid + 1U;
        } else {
            high = mid;
        }
    }

    return false;
}

int main(void)
{
    int arr[] = {2, 4, 7, 10, 15, 23, 42, 56, 78, 91};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int targets[] = {23, 2, 91, 5, 100};
    size_t num_targets = sizeof(targets) / sizeof(targets[0]);
    size_t i;

    for (i = 0U; i < num_targets; i++) {
        size_t found_index = 0U;
        bool found = binary_search(arr, size, targets[i], &found_index);

        if (found) {
            (void)printf("Element %d found at index %zu\n", targets[i], found_index);
        } else {
            (void)printf("Element %d not found in the array\n", targets[i]);
        }
    }

    return 0;
}