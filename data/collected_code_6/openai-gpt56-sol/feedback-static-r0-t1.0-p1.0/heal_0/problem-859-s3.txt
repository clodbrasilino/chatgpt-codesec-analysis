#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int print_all_sublists(const int *list, size_t length)
{
    if (list == NULL && length != 0U) {
        return -1;
    }

    if (length >= sizeof(size_t) * CHAR_BIT) {
        return -1;
    }

    size_t count = (size_t)1U << length;

    for (size_t mask = 0U; mask < count; ++mask) {
        if (putchar('[') == EOF) {
            return -1;
        }

        int first = 1;

        for (size_t i = 0U; i < length; ++i) {
            if ((mask & ((size_t)1U << i)) != 0U) {
                if (!first && printf(", ") < 0) {
                    return -1;
                }

                if (printf("%d", list[i]) < 0) {
                    return -1;
                }

                first = 0;
            }
        }

        if (printf("]\n") < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    int list[] = {1, 2, 3, 4};
    size_t length = sizeof(list) / sizeof(list[0]);

    if (print_all_sublists(list, length) != 0) {
        fprintf(stderr, "Failed to generate sublists.\n");
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to flush output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}