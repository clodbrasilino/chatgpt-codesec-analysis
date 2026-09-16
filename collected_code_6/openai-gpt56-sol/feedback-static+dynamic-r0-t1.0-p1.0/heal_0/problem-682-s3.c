#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int multiply_lists(const int64_t *a,
                          const int64_t *b,
                          int64_t *result,
                          size_t length)
{
    if ((length != 0U) && (a == NULL || b == NULL || result == NULL)) {
        return EINVAL;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (__builtin_mul_overflow(a[i], b[i], &result[i])) {
            return ERANGE;
        }
    }

    return 0;
}

int main(void)
{
    static const int64_t first[] = {2, 4, 6, 8};
    static const int64_t second[] = {3, 5, 7, 9};
    const size_t length = sizeof(first) / sizeof(first[0]);
    int64_t *result = NULL;
    int status = EXIT_FAILURE;

    if (length > SIZE_MAX / sizeof(*result)) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    result = malloc(length * sizeof(*result));
    if (result == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    const int error = multiply_lists(first, second, result, length);
    if (error != 0) {
        fputs(error == ERANGE ? "Multiplication overflow\n"
                             : "Invalid function argument\n",
              stderr);
        goto cleanup;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%" PRId64 "%c",
                   result[i],
                   i + 1U == length ? '\n' : ' ') < 0) {
            fputs("Output failed\n", stderr);
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(result);
    return status;
}