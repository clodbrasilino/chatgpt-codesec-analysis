#include <ctype.h>
#include <errno.h>
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
        int digit = *begin - '0';

        if ((digit % 2) == 0) {
            even_sum += digit;
        } else {
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
    char input[1024];
    char *end;
    char *newline;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    newline = input;
    while (*newline != '\0' && *newline != '\n') {
        ++newline;
    }

    if (*newline != '\n' && !feof(stdin)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    (void)strtoll(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    {
        const char *number_end = end;

        while (isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end != '\0') {
            return EXIT_FAILURE;
        }

        printf("%d\n", digit_sum_difference(input, number_end));
    }

    return EXIT_SUCCESS;
}