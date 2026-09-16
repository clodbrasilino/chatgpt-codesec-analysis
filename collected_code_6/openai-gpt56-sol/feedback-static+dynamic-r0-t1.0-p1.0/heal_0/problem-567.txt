#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sorted(const int *list, size_t length)
{
    if (list == NULL && length != 0U) {
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
    int values[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(values) / sizeof(values[0]);

    if (printf("%s\n", is_sorted(values, length) ? "sorted" : "not sorted") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}