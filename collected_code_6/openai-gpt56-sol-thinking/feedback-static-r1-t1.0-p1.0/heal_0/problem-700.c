#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool count_elements_in_range(const int *list, size_t length, int minimum,
                             int maximum, size_t *count)
{
    size_t total = 0;

    if (count == NULL || (list == NULL && length != 0) || minimum > maximum) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        if (list[i] >= minimum && list[i] <= maximum) {
            ++total;
        }
    }

    *count = total;
    return true;
}

int main(void)
{
    const int list[] = {2, 7, 12, 5, 18, 9, 3, 15};
    const size_t length = sizeof(list) / sizeof(list[0]);
    size_t count = 0;

    if (!count_elements_in_range(list, length, 5, 12, &count)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}