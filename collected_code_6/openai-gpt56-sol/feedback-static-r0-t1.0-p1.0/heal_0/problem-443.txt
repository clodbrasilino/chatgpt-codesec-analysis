#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

static bool find_largest_negative(const int values[], size_t count, int *result)
{
    if (values == NULL || result == NULL || count == 0U) {
        return false;
    }

    bool found = false;
    int largest_negative = 0;

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] < 0 && (!found || values[i] > largest_negative)) {
            largest_negative = values[i];
            found = true;
        }
    }

    if (found) {
        *result = largest_negative;
    }

    return found;
}

int main(void)
{
    const int values[] = {12, -7, 3, -2, -19, 0, 8, -5};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int largest_negative = 0;

    if (!find_largest_negative(values, count, &largest_negative)) {
        if (fputs("No negative number found.\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (printf("Largest negative number: %d\n", largest_negative) < 0) {
        return 1;
    }

    return 0;
}