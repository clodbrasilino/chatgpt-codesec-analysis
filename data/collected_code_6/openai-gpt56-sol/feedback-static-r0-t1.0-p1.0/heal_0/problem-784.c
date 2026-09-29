#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

bool product_of_first_even_and_odd(const int values[], size_t count, long long *product)
{
    if (values == NULL || product == NULL) {
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

    if (!found_even || !found_odd) {
        return false;
    }

    *product = (long long)first_even * (long long)first_odd;
    return true;
}

int main(void)
{
    int values[] = {7, 3, 8, 4, 9, 2};
    size_t count = sizeof(values) / sizeof(values[0]);
    long long product = 0;

    if (!product_of_first_even_and_odd(values, count, &product)) {
        fputs("The list must contain at least one even and one odd number.\n", stderr);
        return 1;
    }

    if (printf("%lld\n", product) < 0) {
        return 1;
    }

    return 0;
}