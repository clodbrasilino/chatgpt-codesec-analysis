#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool find_max_occurrence(const int *arr, size_t size, int *result)
{
    size_t i;
    size_t j;
    size_t max_count;
    int max_item;

    if (arr == NULL || result == NULL || size == 0U) {
        return false;
    }

    max_count = 0U;
    max_item = arr[0];

    for (i = 0U; i < size; i++) {
        size_t count = 0U;
        for (j = 0U; j < size; j++) {
            if (arr[j] == arr[i]) {
                count++;
            }
        }
        if (count > max_count) {
            max_count = count;
            max_item = arr[i];
        }
    }

    *result = max_item;
    return true;
}

int main(void)
{
    int data[] = { 2, 3, 8, 4, 7, 9, 8, 2, 6, 5, 1, 6, 1, 2, 3, 2, 4, 6, 9, 1, 2 };
    size_t size = sizeof(data) / sizeof(data[0]);
    int result;

    if (find_max_occurrence(data, size, &result)) {
        if (printf("Item with maximum occurrences: %d\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "Error: invalid input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}