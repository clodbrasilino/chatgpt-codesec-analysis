#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

bool divide_first_even_by_first_odd(const int values[], size_t count, double *result)
{
    bool even_found = false;
    bool odd_found = false;
    int first_even = 0;
    int first_odd = 0;

    if (values == NULL || result == NULL) {
        return false;
    }

    for (size_t i = 0; i < count && (!even_found || !odd_found); ++i) {
        if (!even_found && values[i] % 2 == 0) {
            first_even = values[i];
            even_found = true;
        } else if (!odd_found && values[i] % 2 != 0) {
            first_odd = values[i];
            odd_found = true;
        }
    }

    if (!even_found || !odd_found || first_odd == 0) {
        return false;
    }

    *result = (double)first_even / (double)first_odd;
    return true;
}

int main(void)
{
    int values[] = {3, 7, 8, 10, 5};
    const size_t count = sizeof values / sizeof values[0];
    double result = 0.0;

    if (!divide_first_even_by_first_odd(values, count, &result)) {
        fputs("Unable to perform division.\n", stderr);
        return 1;
    }

    if (printf("%.6f\n", result) < 0) {
        return 1;
    }

    return 0;
}