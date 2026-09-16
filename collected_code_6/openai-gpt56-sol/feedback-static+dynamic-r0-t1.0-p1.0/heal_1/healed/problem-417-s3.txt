#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static bool find_common_value(const int *values, size_t count, int *result)
{
    if (values == NULL || result == NULL || count < 2U) {
        return false;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        return false;
    }

    int *sorted_values = malloc(count * sizeof(*sorted_values));
    if (sorted_values == NULL) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        sorted_values[i] = values[i];
    }

    qsort(sorted_values, count, sizeof(*sorted_values), compare_ints);

    bool found = false;

    for (size_t i = 1U; i < count; ++i) {
        if (sorted_values[i] == sorted_values[i - 1U]) {
            *result = sorted_values[i];
            found = true;
            break;
        }
    }

    free(sorted_values);
    return found;
}

int main(void)
{
    const int values[] = {1, 2, 3, 2};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int common_value;

    if (find_common_value(values, count, &common_value)) {
        if (printf("%d\n", common_value) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No common element\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}