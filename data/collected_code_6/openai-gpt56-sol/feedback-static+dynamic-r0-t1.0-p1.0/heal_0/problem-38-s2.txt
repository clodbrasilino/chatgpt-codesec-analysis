#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

bool divide_first_even_by_first_odd(const int values[], size_t count, double *result)
{
    if (values == NULL || result == NULL) {
        return false;
    }

    bool found_even = false;
    bool found_odd = false;
    int first_even = 0;
    int first_odd = 0;

    for (size_t i = 0; i < count && (!found_even || !found_odd); ++i) {
        if (!found_even && values[i] % 2 == 0) {
            first_even = values[i];
            found_even = true;
        } else if (!found_odd && values[i] % 2 != 0) {
            first_odd = values[i];
            found_odd = true;
        }
    }

    if (!found_even || !found_odd || first_odd == 0) {
        return false;
    }

    *result = (double)first_even / (double)first_odd;
    return true;
}

int main(void)
{
    int values[] = {7, 4, 9, 12, 15};
    const size_t count = sizeof(values) / sizeof(values[0]);
    double result = 0.0;

    if (!divide_first_even_by_first_odd(values, count, &result)) {
        fputs("Unable to perform the division.\n", stderr);
        return 1;
    }

    if (printf("%.6f\n", result) < 0) {
        return 1;
    }

    return 0;
}