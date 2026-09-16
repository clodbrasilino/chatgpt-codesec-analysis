#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_most_frequent(const int *items, size_t count, int *result,
                       size_t *frequency)
{
    size_t maximum_frequency = 0;
    int maximum_item;

    if (items == NULL || result == NULL || frequency == NULL || count == 0) {
        return 0;
    }

    maximum_item = items[0];

    for (size_t i = 0; i < count; ++i) {
        size_t current_frequency = 0;

        for (size_t j = 0; j < count; ++j) {
            if (items[i] == items[j]) {
                ++current_frequency;
            }
        }

        if (current_frequency > maximum_frequency) {
            maximum_frequency = current_frequency;
            maximum_item = items[i];
        }
    }

    *result = maximum_item;
    *frequency = maximum_frequency;
    return 1;
}

int main(void)
{
    size_t count = 0;
    size_t frequency = 0;
    int most_frequent = 0;
    int *items = NULL;

    if (scanf("%zu", &count) != 1 || count == 0) {
        fputs("Invalid list size\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*items)) {
        fputs("List size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    items = malloc(count * sizeof(*items));
    if (items == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &items[i]) != 1) {
            fputs("Invalid list item\n", stderr);
            free(items);
            return EXIT_FAILURE;
        }
    }

    if (!find_most_frequent(items, count, &most_frequent, &frequency)) {
        fputs("Unable to determine the most frequent item\n", stderr);
        free(items);
        return EXIT_FAILURE;
    }

    if (printf("%d %zu\n", most_frequent, frequency) < 0) {
        free(items);
        return EXIT_FAILURE;
    }

    free(items);
    return EXIT_SUCCESS;
}