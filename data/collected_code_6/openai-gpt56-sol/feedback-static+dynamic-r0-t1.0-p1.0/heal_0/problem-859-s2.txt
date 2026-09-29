#include <stdio.h>
#include <stdlib.h>

static int generate_sublists(const int *list, size_t length)
{
    if (list == NULL && length != 0U) {
        return -1;
    }

    for (size_t start = 0U; start <= length; ++start) {
        printf("[]\n");

        for (size_t end = start + 1U; end <= length; ++end) {
            if (putchar('[') == EOF) {
                return -1;
            }

            for (size_t i = start; i < end; ++i) {
                if (i > start && printf(", ") < 0) {
                    return -1;
                }

                if (printf("%d", list[i]) < 0) {
                    return -1;
                }
            }

            if (printf("]\n") < 0) {
                return -1;
            }
        }

        if (start == length) {
            break;
        }
    }

    return ferror(stdout) ? -1 : 0;
}

int main(void)
{
    const int list[] = {1, 2, 3, 4};
    const size_t length = sizeof(list) / sizeof(list[0]);

    if (generate_sublists(list, length) != 0) {
        fprintf(stderr, "Failed to generate sublists.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}