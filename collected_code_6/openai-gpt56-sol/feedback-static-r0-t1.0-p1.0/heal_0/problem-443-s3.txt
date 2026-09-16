#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool find_largest_negative(const int *values, size_t count, int *result)
{
    bool found = false;
    int largest = 0;

    if (values == NULL || result == NULL) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
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
    int values[] = {12, -7, 3, -2, -15, 8, -1};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int largest_negative = 0;

    if (!find_largest_negative(values, count, &largest_negative)) {
        if (fputs("No negative number found.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Largest negative number: %d\n", largest_negative) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}