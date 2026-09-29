#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

bool difference_of_first_even_and_odd(const int values[], size_t count, int *difference)
{
    bool even_found = false;
    bool odd_found = false;
    int first_even = 0;
    int first_odd = 0;

    if (values == NULL || difference == NULL) {
        return false;
    }

    for (size_t i = 0; i < count && (!even_found || !odd_found); ++i) {
        if (values[i] % 2 == 0) {
            if (!even_found) {
                first_even = values[i];
                even_found = true;
            }
        } else if (!odd_found) {
            first_odd = values[i];
            odd_found = true;
        }
    }

    if (!even_found || !odd_found) {
        return false;
    }

    *difference = first_even - first_odd;
    return true;
}

int main(void)
{
    int values[] = {7, 3, 10, 4, 9};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int difference = 0;

    if (!difference_of_first_even_and_odd(values, count, &difference)) {
        fputs("The list must contain at least one even and one odd number.\n", stderr);
        return 1;
    }

    if (printf("%d\n", difference) < 0) {
        return 1;
    }

    return 0;
}