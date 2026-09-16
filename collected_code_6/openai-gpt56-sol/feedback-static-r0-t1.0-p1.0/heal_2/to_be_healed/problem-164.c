#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool sum_of_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return false;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t paired_divisor = number / divisor;

            if (UINT64_MAX - total < divisor) {
                return false;
            }
            total += divisor;

            if (paired_divisor != divisor) {
                if (UINT64_MAX - total < paired_divisor) {
                    return false;
                }
                total += paired_divisor;
            }
        }
    }

    *sum = total;
    return true;
}

static bool parse_positive_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed == 0 || parsed > UINT64_MAX) {
        return false;
    }

    *value = (uint64_t)parsed;
    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    uint64_t first;
    uint64_t second;
    uint64_t first_sum;
    uint64_t second_sum;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <positive-integer> <positive-integer>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_positive_uint64(argv[1], &first) ||
        !parse_positive_uint64(argv[2], &second)) {
        fprintf(stderr, "Both arguments must be positive 64-bit integers.\n");
        return EXIT_FAILURE;
    }

    if (!sum_of_divisors(first, &first_sum) ||
        !sum_of_divisors(second, &second_sum)) {
        fprintf(stderr, "Unable to compute divisor sums safely.\n");
        return EXIT_FAILURE;
    }

    puts(first_sum == second_sum ? "Same" : "Not same");
    return EXIT_SUCCESS;
}