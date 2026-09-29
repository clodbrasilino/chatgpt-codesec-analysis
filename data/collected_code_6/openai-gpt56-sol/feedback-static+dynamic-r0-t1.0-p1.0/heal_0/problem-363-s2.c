#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int add_k_to_elements(int *values, size_t count, int k)
{
    if (values == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if ((k > 0 && values[i] > INT_MAX - k) ||
            (k < 0 && values[i] < INT_MIN - k)) {
            return -1;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        values[i] += k;
    }

    return 0;
}

int main(void)
{
    int values[] = {1, 2, 3, 4, 5};
    const size_t count = sizeof(values) / sizeof(values[0]);
    const int k = 10;

    if (add_k_to_elements(values, count, k) != 0) {
        fputs("Unable to add k to the elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%d%s", values[i], i + 1U < count ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}