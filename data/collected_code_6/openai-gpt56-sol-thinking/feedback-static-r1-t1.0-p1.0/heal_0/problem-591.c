#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool interchange_first_last(int *list, size_t length)
{
    if (list == NULL || length == 0) {
        return false;
    }

    if (length > 1) {
        int temporary = list[0];
        list[0] = list[length - 1];
        list[length - 1] = temporary;
    }

    return true;
}

int main(void)
{
    int list[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof list / sizeof list[0];

    if (!interchange_first_last(list, length)) {
        fputs("Unable to interchange elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < length; ++index) {
        if (printf("%d%s", list[index], index + 1 < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}