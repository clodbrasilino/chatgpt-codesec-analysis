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
        int digit = (unsigned char)*begin - '0';

        if (digit % 2 == 0) {
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
    char *begin;
    char *end;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    begin = input;
    while (isspace((unsigned char)*begin)) {
        ++begin;
    }

    errno = 0;
    (void)strtoll(begin, &end, 10);

    if (errno == ERANGE || end == begin) {
        return EXIT_FAILURE;
    }

    {
        char *p = end;

        while (isspace((unsigned char)*p)) {
            ++p;
        }

        if (*p != '\0') {
            return EXIT_FAILURE;
        }
    }

    {
        int found_newline = 0;

        for (char *p = input; *p != '\0'; ++p) {
            if (*p == '\n') {
                found_newline = 1;
                break;
            }
        }

        if (!found_newline && !feof(stdin)) {
            int ch;

            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            return EXIT_FAILURE;
        }
    }

    printf("%d\n", digit_sum_difference(begin, end));

    return EXIT_SUCCESS;
}