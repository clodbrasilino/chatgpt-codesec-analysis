#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int digit_sum_difference(const char *begin, const char *end)
{
    int even_sum = 0;
    int odd_sum = 0;

    if (begin < end && (*begin == '+' || *begin == '-')) {
        ++begin;
    }

    while (begin < end) {
        int digit = (unsigned char)*begin - '0';

        if ((digit % 2) == 0) {
            if (even_sum > INT_MAX - digit) {
                return 0;
            }
            even_sum += digit;
        } else {
            if (odd_sum > INT_MAX - digit) {
                return 0;
            }
            odd_sum += digit;
        }

        ++begin;
    }

    return even_sum - odd_sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[4096];
    size_t length;
    const char *begin;
    const char *end;
    const char *number_end;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    begin = input;
    while (isspace((unsigned char)*begin)) {
        ++begin;
    }

    end = begin;
    if (*end == '+' || *end == '-') {
        ++end;
    }

    {
        const char *digits = end;

        while (isdigit((unsigned char)*end)) {
            ++end;
        }

        if (end == digits) {
            return EXIT_FAILURE;
        }
    }

    number_end = end;

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    printf("%d\n", digit_sum_difference(begin, number_end));

    return EXIT_SUCCESS;
}