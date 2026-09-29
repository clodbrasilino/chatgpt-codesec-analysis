#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    uint64_t value = UINT64_C(1);

    if (result == NULL || n == UINT64_C(0)) {
        return -1;
    }

    for (uint64_t i = UINT64_C(2); i <= n; ++i) {
        const uint64_t divisor = gcd_u64(value, i);
        const uint64_t factor = i / divisor;

        if (value > UINT64_MAX / factor) {
            return -1;
        }

        value *= factor;
    }

    *result = value;
    return 0;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        const char *const program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        (void)fprintf(stderr, "Usage: %s <positive integer>\n", program_name);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || end == NULL || *end != '\0' ||
        input == UINTMAX_C(0) || input > UINT64_MAX) {
        (void)fprintf(stderr, "Invalid positive integer.\n");
        return EXIT_FAILURE;
    }

    if (smallest_multiple((uint64_t)input, &result) != 0) {
        (void)fprintf(stderr, "Result exceeds the uint64_t range.\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}