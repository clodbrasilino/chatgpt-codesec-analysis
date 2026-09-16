#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sorted(const int *list, size_t length)
{
    if (length > 0U && list == NULL) {
        return false;
    }

    for (size_t i = 1U; i < length; ++i) {
        if (list[i - 1U] > list[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int list[] = {1, 2, 2, 4, 5};
    const size_t length = sizeof list / sizeof list[0];

    if (printf("%s\n", is_sorted(list, length) ? "Sorted" : "Not sorted") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}