#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_armstrong(unsigned long long number)
{
    unsigned long long temp = number;
    unsigned int digits = 0U;
    unsigned long long sum = 0ULL;

    do {
        ++digits;
        temp /= 10ULL;
    } while (temp != 0ULL);

    temp = number;

    do {
        const unsigned long long digit = temp % 10ULL;
        unsigned long long power = 1ULL;

        for (unsigned int i = 0U; i < digits; ++i) {
            if (digit != 0ULL && power > ULLONG_MAX / digit) {
                return false;
            }
            power *= digit;
        }

        if (sum > ULLONG_MAX - power) {
            return false;
        }

        sum += power;
        temp /= 10ULL;
    } while (temp != 0ULL);

    return sum == number;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    unsigned long long number;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (input[0] == '-') {
        printf("Not an Armstrong number\n");
        return EXIT_SUCCESS;
    }

    errno = 0;
    number = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    printf("%s\n", is_armstrong(number)
                       ? "Armstrong number"
                       : "Not an Armstrong number");

    return EXIT_SUCCESS;
}