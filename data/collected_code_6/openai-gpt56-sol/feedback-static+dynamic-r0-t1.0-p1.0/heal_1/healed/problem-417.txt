#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool find_common_first(const int *values, size_t count, int *result)
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
    int common_first;

    if (!find_common_first(values, count, &common_first)) {
        if (fprintf(stderr, "No common element found.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Common element: %d\n", common_first) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}