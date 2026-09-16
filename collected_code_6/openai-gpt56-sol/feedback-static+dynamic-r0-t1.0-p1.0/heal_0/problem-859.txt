#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int print_sublists(const int *list, size_t length)
{
    if (length > 0 && list == NULL) {
        return -1;
    }

    if (puts("[]") == EOF) {
        return -1;
    }

    for (size_t start = 0; start < length; ++start) {
        for (size_t end = start; end < length; ++end) {
            if (putchar('[') == EOF) {
                return -1;
            }

            for (size_t i = start; i <= end; ++i) {
                if (i > start && fputs(", ", stdout) == EOF) {
                    return -1;
                }

                if (printf("%d", list[i]) < 0) {
                    return -1;
                }
            }

            if (puts("]") == EOF) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    int *list = NULL;
    size_t length;

    if (printf("Enter the number of elements: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*list)) {
        fputs("List is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0) {
        list = malloc(length * sizeof(*list));
        if (list == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }

        if (printf("Enter %zu integers: ", length) < 0) {
            free(list);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            if (scanf("%d", &list[i]) != 1) {
                fputs("Invalid element.\n", stderr);
                free(list);
                return EXIT_FAILURE;
            }
        }
    }

    if (print_sublists(list, length) != 0) {
        fputs("Output error.\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    free(list);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}