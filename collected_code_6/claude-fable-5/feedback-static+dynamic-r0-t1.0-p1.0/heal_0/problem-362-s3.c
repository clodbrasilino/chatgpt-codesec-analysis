#include <stdio.h>
#include <stdlib.h>

int find_max_occurrence(const int *arr, size_t n, int *result)
{
    if (arr == NULL || n == 0 || result == NULL) {
        return -1;
    }

    size_t max_count = 0;
    int max_item = arr[0];

    for (size_t i = 0; i < n; i++) {
        size_t count = 0;
        for (size_t j = 0; j < n; j++) {
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
    return 0;
}

int main(void)
{
    int list[] = { 2, 3, 8, 4, 7, 9, 8, 2, 6, 5, 1, 6, 1, 2, 3, 2, 4, 6, 9, 1, 2 };
    size_t n = sizeof(list) / sizeof(list[0]);
    int result;

    if (find_max_occurrence(list, n, &result) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Item with maximum occurrences: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}