#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_true(const bool values[], size_t length)
{
    size_t count = 0U;

    if (values == NULL && length != 0U) {
        return 0U;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (values[i]) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    const bool values[] = {true, false, true, true, false};
    const size_t length = sizeof(values) / sizeof(values[0]);

    if (printf("%zu\n", count_true(values, length)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}