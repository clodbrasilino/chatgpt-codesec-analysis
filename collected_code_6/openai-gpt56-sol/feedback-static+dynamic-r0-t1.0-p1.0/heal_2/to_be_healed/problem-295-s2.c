#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_divisors(uint64_t number, uint64_t *result)
{
    uint64_t sum = 0;

    if (number == 0 || result == NULL) {
        return 0;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t paired_divisor = number / divisor;

            if (UINT64_MAX - sum < divisor) {
                return 0;
            }
            sum += divisor;

            if (paired_divisor != divisor) {
                if (UINT64_MAX - sum < paired_divisor) {
                    return 0;
                }
                sum += paired_divisor;
            }
        }
    }

    *result = sum;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t number;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    end = input;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed == 0 || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    number = (uint64_t)parsed;

    if (!sum_of_divisors(number, &sum)) {
        fprintf(stderr, "Unable to calculate the divisor sum\n");
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}