#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool find_largest_negative(const int *values, size_t count, int *result)
{
    if (values == NULL || result == NULL || count == 0U) {
        return false;
    }

    bool found = false;
    int largest = 0;

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] < 0 && (!found || values[i] > largest)) {
            largest = values[i];
            found = true;
        }
    }

    if (found) {
        *result = largest;
    }

    return found;
}

int main(void)
{
    int values[] = {12, -7, 3, -2, -18, 0, 9};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int largest_negative = 0;

    if (!find_largest_negative(values, count, &largest_negative)) {
        if (fprintf(stderr, "No negative number found.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%d\n", largest_negative) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}