#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_squares(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b = n + 1U;
    uint64_t c;

    if (result == NULL || n == UINT64_MAX) {
        return -1;
    }

    if (n > (UINT64_MAX - 1U) / 2U) {
        return -1;
    }

    c = (2U * n) + 1U;

    if ((a % 2U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if ((a % 3U) == 0U) {
        a /= 3U;
    } else if ((b % 3U) == 0U) {
        b /= 3U;
    } else {
        c /= 3U;
    }

    if (a != 0U && b > UINT64_MAX / a) {
        return -1;
    }

    a *= b;

    if (a != 0U && c > UINT64_MAX / a) {
        return -1;
    }

    *result = a * c;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > UINT64_MAX) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (sum_of_squares((uint64_t)input, &result) != 0) {
        (void)fprintf(stderr, "Result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}