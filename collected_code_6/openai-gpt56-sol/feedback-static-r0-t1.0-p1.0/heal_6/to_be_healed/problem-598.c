#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_space_without_newline(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\f' || ch == '\v';
}

static bool is_armstrong(unsigned long long number)
{
    unsigned long long temp = number;
    unsigned long long sum = 0;
    unsigned int digits = 0;

    do {
        ++digits;
        temp /= 10;
    } while (temp != 0);

    temp = number;

    do {
        unsigned long long digit = temp % 10;
        unsigned long long power = 1;

        for (unsigned int i = 0; i < digits; ++i) {
            if (digit != 0 && power > ULLONG_MAX / digit) {
                return false;
            }
            power *= digit;
        }

        if (sum > ULLONG_MAX - power) {
            return false;
        }

        sum += power;
        temp /= 10;
    } while (temp != 0);

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

    size_t length = 0;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        return EXIT_FAILURE;
    }

    char *start = input;

    while (is_space_without_newline((unsigned char)*start)) {
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

    while (is_space_without_newline((unsigned char)*end)) {
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