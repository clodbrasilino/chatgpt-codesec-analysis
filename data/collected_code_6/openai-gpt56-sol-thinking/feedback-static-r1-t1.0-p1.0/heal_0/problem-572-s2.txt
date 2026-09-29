#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool remove_duplicate_numbers(int *numbers, size_t count, size_t *new_count)
{
    size_t unique_count = 0;

    if (new_count == NULL || (numbers == NULL && count != 0)) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        bool duplicate = false;

        for (size_t j = 0; j < unique_count; ++j) {
            if (numbers[j] == numbers[i]) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            numbers[unique_count++] = numbers[i];
        }
    }

    *new_count = unique_count;
    return true;
}

int main(void)
{
    size_t list_count;

    if (scanf("%zu", &list_count) != 1) {
        return EXIT_FAILURE;
    }

    for (size_t list_index = 0; list_index < list_count; ++list_index) {
        size_t count;
        size_t unique_count;
        int *numbers = NULL;

        if (scanf("%zu", &count) != 1) {
            return EXIT_FAILURE;
        }

        if (count > SIZE_MAX / sizeof(*numbers)) {
            return EXIT_FAILURE;
        }

        if (count != 0) {
            numbers = malloc(count * sizeof(*numbers));
            if (numbers == NULL) {
                return EXIT_FAILURE;
            }
        }

        for (size_t i = 0; i < count; ++i) {
            if (scanf("%d", &numbers[i]) != 1) {
                free(numbers);
                return EXIT_FAILURE;
            }
        }

        if (!remove_duplicate_numbers(numbers, count, &unique_count)) {
            free(numbers);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < unique_count; ++i) {
            if (i != 0 && putchar(' ') == EOF) {
                free(numbers);
                return EXIT_FAILURE;
            }

            if (printf("%d", numbers[i]) < 0) {
                free(numbers);
                return EXIT_FAILURE;
            }
        }

        if (putchar('\n') == EOF) {
            free(numbers);
            return EXIT_FAILURE;
        }

        free(numbers);
    }

    return EXIT_SUCCESS;
}