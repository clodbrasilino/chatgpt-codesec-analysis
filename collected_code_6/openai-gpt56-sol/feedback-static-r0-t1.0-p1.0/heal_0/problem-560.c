#include <stdio.h>
#include <stdlib.h>

static int contains(const int *values, size_t count, int value)
{
    for (size_t i = 0; i < count; ++i) {
        if (values[i] == value) {
            return 1;
        }
    }

    return 0;
}

static int tuple_union(const int *first, size_t first_count,
                       const int *second, size_t second_count,
                       int **result, size_t *result_count)
{
    if (result == NULL || result_count == NULL ||
        (first_count > 0 && first == NULL) ||
        (second_count > 0 && second == NULL)) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (first_count > SIZE_MAX - second_count) {
        return -1;
    }

    size_t capacity = first_count + second_count;

    if (capacity == 0) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    int *values = malloc(capacity * sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    size_t count = 0;

    for (size_t i = 0; i < first_count; ++i) {
        if (!contains(values, count, first[i])) {
            values[count++] = first[i];
        }
    }

    for (size_t i = 0; i < second_count; ++i) {
        if (!contains(values, count, second[i])) {
            values[count++] = second[i];
        }
    }

    *result = values;
    *result_count = count;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 4};
    const int second[] = {3, 4, 5, 6, 6};
    int *result = NULL;
    size_t result_count = 0;

    if (tuple_union(first, sizeof(first) / sizeof(first[0]),
                    second, sizeof(second) / sizeof(second[0]),
                    &result, &result_count) != 0) {
        fputs("Unable to compute the union.\n", stderr);
        return EXIT_FAILURE;
    }

    putchar('(');

    for (size_t i = 0; i < result_count; ++i) {
        if (i > 0) {
            fputs(", ", stdout);
        }

        printf("%d", result[i]);
    }

    puts(")");
    free(result);
    return EXIT_SUCCESS;
}