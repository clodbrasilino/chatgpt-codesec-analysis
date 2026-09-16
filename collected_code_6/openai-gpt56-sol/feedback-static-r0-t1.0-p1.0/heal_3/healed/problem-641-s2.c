#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nonagonal_number(uint64_t n, uint64_t *result)
{
    uint64_t factor;

    if (result == NULL || n == 0U || n > (UINT64_MAX - 5U) / 7U) {
        return 0;
    }

    factor = 7U * n - 5U;

    if ((n & 1U) == 0U) {
        n /= 2U;
    } else {
        factor /= 2U;
    }

    if (factor > UINT64_MAX / n) {
        return 0;
    }

    *result = n * factor;
    return 1;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == 0U || input > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!nonagonal_number((uint64_t)input, &result)) {
        fputs("Result is outside the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}