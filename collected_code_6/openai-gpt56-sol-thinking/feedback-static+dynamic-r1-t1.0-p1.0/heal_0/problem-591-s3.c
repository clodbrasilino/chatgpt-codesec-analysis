#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool interchange_first_last(int *list, size_t length)
{
    if (list == NULL || length == 0U) {
        return false;
    }

    if (length > 1U) {
        int temporary = list[0];
        list[0] = list[length - 1U];
        list[length - 1U] = temporary;
    }

    return true;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    const size_t length = sizeof(list) / sizeof(list[0]);

    if (!interchange_first_last(list, length)) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        if (printf("%d%s", list[index], index + 1U < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}