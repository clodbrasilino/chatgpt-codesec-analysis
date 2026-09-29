#include <stdio.h>
#include <stdlib.h>

static size_t count_positive(const int *values, size_t length)
{
    size_t count = 0U;

    if (values == NULL) {
        return 0U;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (values[i] > 0) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    int values[] = {-4, 7, 0, 12, -3, 5};
    const size_t length = sizeof values / sizeof values[0];
    const size_t count = count_positive(values, length);

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}