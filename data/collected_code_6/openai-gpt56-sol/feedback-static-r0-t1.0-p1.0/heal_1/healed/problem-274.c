#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_index_binomial(unsigned int n, uintmax_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = UINTMAX_C(1);
        return 1;
    }

    if (n > (unsigned int)(sizeof(uintmax_t) * CHAR_BIT)) {
        return 0;
    }

    *result = UINTMAX_C(1) << (n - 1U);
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uintmax_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        input > (uintmax_t)UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!sum_even_index_binomial((unsigned int)input, &result)) {
        fprintf(stderr, "Result cannot be represented\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", result);
    return EXIT_SUCCESS;
}