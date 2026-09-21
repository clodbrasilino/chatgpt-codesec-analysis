#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_elements_equal(const int *list, size_t length)
{
    if (list == NULL || length == 0U) {
        return false;
    }

    for (size_t i = 1U; i < length; ++i) {
        if (list[i] != list[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t length;

    if (fputs("Enter the number of elements: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &length) != 1 ||
        length == 0U ||
        length > SIZE_MAX / sizeof(int)) {
        fputs("Invalid list length.\n", stderr);
        return EXIT_FAILURE;
    }

    int *list = malloc(length * sizeof(*list));
    if (list == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu integers: ", length) < 0 ||
        fflush(stdout) == EOF) {
        free(list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &list[i]) != 1) {
            fputs("Invalid input.\n", stderr);
            free(list);
            return EXIT_FAILURE;
        }
    }

    const bool equal = all_elements_equal(list, length);

    if (puts(equal
                 ? "All elements are the same."
                 : "The elements are not all the same.") == EOF) {
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}