#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int extract_singletons(const int *values, size_t count,
                              int **singletons, size_t *singleton_count)
{
    size_t unique_count = 0;
    size_t output_index = 0;

    if (singletons == NULL || singleton_count == NULL ||
        (count > 0 && values == NULL)) {
        return -1;
    }

    *singletons = NULL;
    *singleton_count = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t occurrences = 0;

        for (size_t j = 0; j < count; ++j) {
            if (values[i] == values[j]) {
                ++occurrences;
            }
        }

        if (occurrences == 1) {
            ++unique_count;
        }
    }

    if (unique_count == 0) {
        return 0;
    }

    if (unique_count > SIZE_MAX / sizeof **singletons) {
        return -1;
    }

    *singletons = malloc(unique_count * sizeof **singletons);
    if (*singletons == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t occurrences = 0;

        for (size_t j = 0; j < count; ++j) {
            if (values[i] == values[j]) {
                ++occurrences;
            }
        }

        if (occurrences == 1) {
            (*singletons)[output_index++] = values[i];
        }
    }

    *singleton_count = unique_count;
    return 0;
}

int main(void)
{
    size_t count;
    int *values = NULL;
    int *singletons = NULL;
    size_t singleton_count = 0;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof *values) {
        return EXIT_FAILURE;
    }

    if (count > 0) {
        values = malloc(count * sizeof *values);
        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (extract_singletons(values, count, &singletons,
                           &singleton_count) != 0) {
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < singleton_count; ++i) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", singletons[i]);
    }
    putchar('\n');

    free(singletons);
    free(values);
    return EXIT_SUCCESS;
}