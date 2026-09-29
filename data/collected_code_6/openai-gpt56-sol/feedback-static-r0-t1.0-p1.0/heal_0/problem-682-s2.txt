#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int multiply_lists(const long *a, const long *b, long *result, size_t length)
{
    if ((length > 0U) && ((a == NULL) || (b == NULL) || (result == NULL))) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (__builtin_mul_overflow(a[i], b[i], &result[i])) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const long first[] = {1L, 2L, 3L, 4L, 5L};
    const long second[] = {6L, 7L, 8L, 9L, 10L};
    const size_t length = sizeof(first) / sizeof(first[0]);
    long *result = NULL;
    int status = EXIT_FAILURE;

    if (length > SIZE_MAX / sizeof(*result)) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    result = malloc(length * sizeof(*result));
    if (result == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    if (multiply_lists(first, second, result, length) != 0) {
        fputs("Multiplication failed\n", stderr);
        goto cleanup;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%ld%s", result[i], (i + 1U == length) ? "\n" : " ") < 0) {
            fputs("Output failed\n", stderr);
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    return status;
}