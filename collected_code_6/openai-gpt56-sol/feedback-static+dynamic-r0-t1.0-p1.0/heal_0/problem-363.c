#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int add_k_to_elements(const int *tuple, size_t length, int k, int *result)
{
    if ((tuple == NULL || result == NULL) && length > 0U) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        if ((k > 0 && tuple[i] > INT_MAX - k) ||
            (k < 0 && tuple[i] < INT_MIN - k)) {
            return -1;
        }
        result[i] = tuple[i] + k;
    }

    return 0;
}

int main(void)
{
    const int tuple[] = {1, 2, 3, 4, 5};
    const size_t length = sizeof(tuple) / sizeof(tuple[0]);
    const int k = 10;

    if (length > SIZE_MAX / sizeof(int)) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    int *result = malloc(length * sizeof(*result));
    if (result == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    if (add_k_to_elements(tuple, length, k, result) != 0) {
        fputs("Unable to add k to the tuple elements\n", stderr);
        free(result);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%d%s", result[i], i + 1U == length ? "\n" : " ") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}