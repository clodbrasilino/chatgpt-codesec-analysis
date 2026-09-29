#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_elements_same(const int *list, size_t length)
{
    if (list == NULL || length == 0U) {
        return false;
    }

    for (size_t i = 1U; i < length; ++i) {
        if (list[i] != list[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int list[] = {7, 7, 7, 7, 7};
    const size_t length = sizeof(list) / sizeof(list[0]);

    if (all_elements_same(list, length)) {
        if (puts("All elements are the same.") == EOF) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("The elements are not all the same.") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}