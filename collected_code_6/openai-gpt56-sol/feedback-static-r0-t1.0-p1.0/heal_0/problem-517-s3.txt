#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

bool find_largest_positive(const int values[], size_t count, int *largest)
{
    if (values == NULL || largest == NULL || count == 0U) {
        return false;
    }

    bool found = false;
    int maximum = 0;

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] > 0 && (!found || values[i] > maximum)) {
            maximum = values[i];
            found = true;
        }
    }

    if (found) {
        *largest = maximum;
    }

    return found;
}

int main(void)
{
    const int values[] = {-12, 7, 24, -3, 18, 0, 31, 5};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int largest = 0;

    if (!find_largest_positive(values, count, &largest)) {
        if (fputs("No positive number found.\n", stderr) == EOF) {
            return 1;
        }
        return 1;
    }

    if (printf("Largest positive number: %d\n", largest) < 0) {
        return 1;
    }

    return 0;
}