#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool find_common_value(const int *values, size_t count, int *result)
{
    if (values == NULL || result == NULL || count == 0U) {
        return false;
    }

    const int candidate = values[0];

    for (size_t i = 1U; i < count; ++i) {
        if (values[i] != candidate) {
            return false;
        }
    }

    *result = candidate;
    return true;
}

int main(void)
{
    const int values[] = {10, 10, 10, 10};
    const size_t count = sizeof values / sizeof values[0];
    int common_value;

    if (!find_common_value(values, count, &common_value)) {
        if (fprintf(stderr, "No common value found.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Common value: %d\n", common_value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}