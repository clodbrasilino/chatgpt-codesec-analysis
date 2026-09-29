#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedral_number(uint64_t n, uint64_t *result)
{
    uint64_t factors[3] = {n, n + 1U, n + 2U};
    const uint64_t divisors[2] = {2U, 3U};

    if (result == NULL || n > UINT64_MAX - 2U) {
        return -1;
    }

    for (size_t i = 0; i < 2U; ++i) {
        for (size_t j = 0; j < 3U; ++j) {
            if (factors[j] % divisors[i] == 0U) {
                factors[j] /= divisors[i];
                break;
            }
        }
    }

    if (factors[0] != 0U && factors[1] > UINT64_MAX / factors[0]) {
        return -1;
    }

    uint64_t value = factors[0] * factors[1];

    if (factors[2] != 0U && value > UINT64_MAX / factors[2]) {
        return -1;
    }

    *result = value * factors[2];
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (tetrahedral_number((uint64_t)input, &result) != 0) {
        fprintf(stderr, "Result cannot be represented as uint64_t\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}