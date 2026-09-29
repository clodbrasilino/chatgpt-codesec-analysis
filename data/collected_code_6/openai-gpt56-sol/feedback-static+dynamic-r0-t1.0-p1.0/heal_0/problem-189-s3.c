#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int first_missing_positive(int *values, size_t count, size_t *result)
{
    size_t i;

    if (result == NULL || (values == NULL && count != 0U) || count == SIZE_MAX) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        while (values[i] > 0 && (size_t)values[i] <= count) {
            size_t target = (size_t)values[i] - 1U;
            int temporary;

            if (values[target] == values[i]) {
                break;
            }

            temporary = values[i];
            values[i] = values[target];
            values[target] = temporary;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (values[i] <= 0 || (size_t)values[i] != i + 1U) {
            *result = i + 1U;
            return 0;
        }
    }

    *result = count + 1U;
    return 0;
}

int main(void)
{
    int values[] = {3, 4, -1, 1};
    const size_t count = sizeof(values) / sizeof(values[0]);
    size_t missing = 0U;

    if (first_missing_positive(values, count, &missing) != 0) {
        fputs("Unable to determine the first missing positive number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", missing) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}