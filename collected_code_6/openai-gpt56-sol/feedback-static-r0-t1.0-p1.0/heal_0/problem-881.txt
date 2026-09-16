#include <stdio.h>
#include <stdlib.h>

static int sum_first_even_and_odd(const int values[], size_t count, int *sum)
{
    int even = 0;
    int odd = 0;
    int found_even = 0;
    int found_odd = 0;

    if (values == NULL || sum == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count && (!found_even || !found_odd); ++i) {
        if (values[i] % 2 == 0 && !found_even) {
            even = values[i];
            found_even = 1;
        } else if (values[i] % 2 != 0 && !found_odd) {
            odd = values[i];
            found_odd = 1;
        }
    }

    if (!found_even || !found_odd) {
        return 0;
    }

    *sum = even + odd;
    return 1;
}

int main(void)
{
    int values[] = {5, 7, 8, 10, 3, 2};
    size_t count = sizeof(values) / sizeof(values[0]);
    int sum = 0;

    if (!sum_first_even_and_odd(values, count, &sum)) {
        fputs("The list must contain at least one even and one odd number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}