#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *values, size_t count, int target)
{
    for (size_t i = 0; i < count; ++i) {
        if (values[i] == target) {
            return true;
        }
    }

    return false;
}

static int *find_dissimilar(const int *first, size_t first_count,
                            const int *second, size_t second_count,
                            size_t *result_count)
{
    if (result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    if ((first == NULL && first_count != 0) ||
        (second == NULL && second_count != 0) ||
        first_count > SIZE_MAX - second_count) {
        return NULL;
    }

    size_t capacity = first_count + second_count;

    if (capacity > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *result = malloc((capacity == 0 ? 1 : capacity) * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < first_count; ++i) {
        if (!contains(second, second_count, first[i])) {
            result[(*result_count)++] = first[i];
        }
    }

    for (size_t i = 0; i < second_count; ++i) {
        if (!contains(first, first_count, second[i])) {
            result[(*result_count)++] = second[i];
        }
    }

    if (*result_count > 0) {
        int *resized = realloc(result, *result_count * sizeof(*result));
        if (resized != NULL) {
            result = resized;
        }
    }

    return result;
}

static void print_values(const int *values, size_t count)
{
    putchar('[');

    for (size_t i = 0; i < count; ++i) {
        if (i > 0) {
            fputs(", ", stdout);
        }
        printf("%d", values[i]);
    }

    puts("]");
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {4, 5, 6, 7, 8};
    size_t result_count = 0;

    int *result = find_dissimilar(
        first, sizeof(first) / sizeof(first[0]),
        second, sizeof(second) / sizeof(second[0]),
        &result_count
    );

    if (result == NULL) {
        fputs("Unable to compute dissimilar elements.\n", stderr);
        return EXIT_FAILURE;
    }

    print_values(result, result_count);
    free(result);

    return EXIT_SUCCESS;
}