#include <stdio.h>
#include <stdlib.h>

static int print_repeated_elements(const int *elements, const size_t *counts,
                                   size_t length)
{
    if ((elements == NULL || counts == NULL) && length != 0U) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        for (size_t j = 0U; j < counts[i]; ++j) {
            if (printf("%d\n", elements[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    const int elements[] = {10, 20, 30, 40};
    const size_t counts[] = {2U, 1U, 3U, 2U};
    const size_t length = sizeof(elements) / sizeof(elements[0]);

    if (length != sizeof(counts) / sizeof(counts[0])) {
        return EXIT_FAILURE;
    }

    if (print_repeated_elements(elements, counts, length) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}