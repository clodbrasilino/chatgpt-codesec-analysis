#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_armstrong(unsigned long long number)
{
    unsigned long long temp = number;
    unsigned long long sum = 0ULL;
    unsigned int digits = 0U;

    do {
        ++digits;
        temp /= 10ULL;
    } while (temp != 0ULL);

    temp = number;

    do {
        unsigned long long digit = temp % 10ULL;
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

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0U;

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        return EXIT_FAILURE;
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return EXIT_FAILURE;
        }
    }

    char *start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        puts("Not an Armstrong number");
        return EXIT_SUCCESS;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_armstrong(number)
             ? "Armstrong number"
             : "Not an Armstrong number");

    return EXIT_SUCCESS;
}