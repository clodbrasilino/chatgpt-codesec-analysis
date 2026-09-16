#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != UINT64_C(0)) {
        const uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int smallest_multiple(uint64_t n, uint64_t *result)
{
    uint64_t multiple = UINT64_C(1);

    if (result == NULL || n == UINT64_C(0)) {
        return 0;
    }

    for (uint64_t i = UINT64_C(2); i <= n; ++i) {
        const uint64_t factor = i / gcd_u64(multiple, i);

        if (multiple > UINT64_MAX / factor) {
            return 0;
        }

        multiple *= factor;
    }

    *result = multiple;
    return 1;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed == UINTMAX_C(0) || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer.\n");
        return EXIT_FAILURE;
    }

    if (!smallest_multiple((uint64_t)parsed, &result)) {
        fprintf(stderr, "Result exceeds the uint64_t range.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}