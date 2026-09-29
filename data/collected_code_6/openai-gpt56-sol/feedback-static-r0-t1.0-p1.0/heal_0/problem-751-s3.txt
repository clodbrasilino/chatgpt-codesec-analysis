#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_min_heap(const int array[], size_t length)
{
    if (array == NULL) {
        return length == 0U;
    }

    for (size_t parent = 0U; parent < length / 2U; ++parent) {
        size_t left = 2U * parent + 1U;
        size_t right = left + 1U;

        if (array[parent] > array[left]) {
            return false;
        }

        if (right < length && array[parent] > array[right]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        fputs("Array size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (length > 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }

        for (size_t i = 0U; i < length; ++i) {
            if (scanf("%d", &array[i]) != 1) {
                fputs("Invalid input\n", stderr);
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    puts(is_min_heap(array, length) ? "Min heap" : "Not a min heap");

    free(array);
    return EXIT_SUCCESS;
}