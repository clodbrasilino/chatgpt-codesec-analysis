#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int find_second_smallest(const int *values, size_t count, int *result)
{
    int smallest;
    int second_smallest;
    int has_second = 0;
    size_t i;

    if (values == NULL || result == NULL || count < 2U) {
        return -1;
    }

    smallest = values[0];

    for (i = 1U; i < count; ++i) {
        if (values[i] < smallest) {
            second_smallest = smallest;
            smallest = values[i];
            has_second = 1;
        } else if (values[i] > smallest &&
                   (!has_second || values[i] < second_smallest)) {
            second_smallest = values[i];
            has_second = 1;
        }
    }

    if (!has_second) {
        return -1;
    }

    *result = second_smallest;
    return 0;
}

int main(void)
{
    size_t count;
    int *values;
    int second_smallest;
    size_t i;

    if (printf("Enter the number of elements: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &count) != 1 || count < 2U ||
        count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Invalid element count.\n");
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu integers: ", count) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (find_second_smallest(values, count, &second_smallest) != 0) {
        fprintf(stderr, "No distinct second smallest number exists.\n");
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("Second smallest number: %d\n", second_smallest) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}