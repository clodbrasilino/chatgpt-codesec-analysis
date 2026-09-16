#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nonagonal_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > UINT64_MAX / UINT64_C(7)) {
        return 0;
    }

    uint64_t factor = UINT64_C(7) * n - UINT64_C(5);

    if ((n & UINT64_C(1)) == 0) {
        n /= UINT64_C(2);
    } else {
        factor /= UINT64_C(2);
    }

    if (factor != 0 && n > UINT64_MAX / factor) {
        return 0;
    }

    *result = n * factor;
    return 1;
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *const input_string = argv[1];
    char *end = NULL;

    errno = 0;
    const uintmax_t input = strtoumax(input_string, &end, 10);

    if (errno == ERANGE ||
        end == input_string ||
        *end != '\0' ||
        input == 0 ||
        input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result;
    if (!nonagonal_number((uint64_t)input, &result)) {
        fprintf(stderr, "Result is outside the uint64_t range\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}