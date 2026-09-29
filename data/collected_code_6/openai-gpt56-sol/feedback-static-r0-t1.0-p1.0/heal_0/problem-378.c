#include <stdio.h>
#include <stdlib.h>

static int shift_last_to_first(int *list, size_t length)
{
    if (list == NULL || length == 0) {
        return -1;
    }

    if (length > 1) {
        int last = list[length - 1];

        for (size_t i = length - 1; i > 0; --i) {
            list[i] = list[i - 1];
        }

        list[0] = last;
    }

    return 0;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(list) / sizeof(list[0]);

    if (shift_last_to_first(list, length) != 0) {
        fputs("Unable to shift the list.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", list[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}