#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_factor_sum(uint64_t number, uint64_t *result)
{
    uint64_t sum = 0;
    uint64_t factor = 2;

    if (number < 2 || result == NULL) {
        return -1;
    }

    while (factor <= number / factor) {
        while (number % factor == 0) {
            if (UINT64_MAX - sum < factor) {
                return -1;
            }

            sum += factor;
            number /= factor;
        }

        factor = (factor == 2) ? 3 : factor + 2;
    }

    if (number > 1) {
        if (UINT64_MAX - sum < number) {
            return -1;
        }

        sum += number;
    }

    *result = sum;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer greater than 1>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed < UINT64_C(2) || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (minimum_factor_sum((uint64_t)parsed, &result) != 0) {
        fprintf(stderr, "Unable to compute result\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}