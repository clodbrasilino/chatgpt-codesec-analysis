#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nonagonal_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > UINT64_MAX / 7) {
        return 0;
    }

    uint64_t factor = 7 * n - 5;

    if ((n & UINT64_C(1)) == 0) {
        n /= 2;
    } else {
        factor /= 2;
    }

    if (factor != 0 && n > UINT64_MAX / factor) {
        return 0;
    }

    *result = n * factor;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
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