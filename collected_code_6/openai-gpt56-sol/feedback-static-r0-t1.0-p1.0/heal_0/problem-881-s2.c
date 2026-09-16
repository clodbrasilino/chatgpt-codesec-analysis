#include <stdio.h>
#include <stdlib.h>

static int sum_first_even_and_odd(const int *values, size_t count, int *sum)
{
    int even = 0;
    int odd = 0;
    int found_even = 0;
    int found_odd = 0;

    if (values == NULL || sum == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count && (!found_even || !found_odd); ++i) {
        if (values[i] % 2 == 0) {
            if (!found_even) {
                even = values[i];
                found_even = 1;
            }
        } else if (!found_odd) {
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
    size_t count = 0;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    int sum = 0;
    if (!sum_first_even_and_odd(values, count, &sum)) {
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", sum) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}