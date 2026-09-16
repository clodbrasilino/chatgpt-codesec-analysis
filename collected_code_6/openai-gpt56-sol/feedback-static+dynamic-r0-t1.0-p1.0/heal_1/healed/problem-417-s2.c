#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool find_common_first(const int *values, size_t count, int *result)
{
    if (values == NULL || result == NULL || count == 0) {
        return false;
    }

    int candidate = values[0];

    for (size_t i = 1; i < count; ++i) {
        if (values[i] != candidate) {
            return false;
        }
    }

    *result = candidate;
    return true;
}

int main(void)
{
    const int values[] = {5, 5, 5};
    const size_t count = sizeof values / sizeof values[0];
    int common_first;

    if (!find_common_first(values, count, &common_first)) {
        fputs("No common element found.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", common_first) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}