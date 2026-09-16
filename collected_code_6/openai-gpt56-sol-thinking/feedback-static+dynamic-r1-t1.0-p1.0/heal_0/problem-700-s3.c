#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool count_elements_in_range(const int *list, size_t length,
                             int lower, int upper, size_t *count)
{
    size_t result = 0;

    if (count == NULL || (list == NULL && length != 0) || lower > upper) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        if (list[i] >= lower && list[i] <= upper) {
            ++result;
        }
    }

    *count = result;
    return true;
}

int main(void)
{
    const int list[] = {1, 4, 7, 10, 13, 16, 19};
    const size_t length = sizeof(list) / sizeof(list[0]);
    size_t count = 0;

    if (!count_elements_in_range(list, length, 5, 15, &count)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}