#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

static bool product_of_first_even_and_odd(const int *values, size_t count,
                                          int64_t *product)
{
    bool found_even = false;
    bool found_odd = false;
    int64_t even = 0;
    int64_t odd = 0;

    if (values == NULL || product == NULL) {
        return false;
    }

    for (size_t i = 0; i < count && (!found_even || !found_odd); ++i) {
        if (values[i] % 2 == 0) {
            if (!found_even) {
                even = values[i];
                found_even = true;
            }
        } else if (!found_odd) {
            odd = values[i];
            found_odd = true;
        }
    }

    if (!found_even || !found_odd) {
        return false;
    }

    *product = even * odd;
    return true;
}

int main(void)
{
    const int values[] = {7, 4, 9, 2, 6};
    const size_t count = sizeof values / sizeof values[0];
    int64_t product;

    if (!product_of_first_even_and_odd(values, count, &product)) {
        fputs("The list must contain at least one even and one odd number.\n",
              stderr);
        return 1;
    }

    if (printf("%" PRId64 "\n", product) < 0) {
        return 1;
    }

    return 0;
}