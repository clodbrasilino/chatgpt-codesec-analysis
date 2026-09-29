#include <stdio.h>
#include <stdlib.h>

static int print_consecutive_pairs(const int *items, size_t count)
{
    if (items == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i + 1U < count; ++i) {
        if (printf("(%d, %d)\n", items[i], items[i + 1U]) < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const int items[] = {1, 2, 3, 4, 5};
    const size_t count = sizeof(items) / sizeof(items[0]);

    if (print_consecutive_pairs(items, count) != 0) {
        fputs("Failed to print consecutive pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush standard output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}