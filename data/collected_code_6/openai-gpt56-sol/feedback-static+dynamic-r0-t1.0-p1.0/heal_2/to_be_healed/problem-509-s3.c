#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int average_of_odds(unsigned long long limit, long double *average)
{
    if (average == NULL || limit == 0 || limit % 2 == 0) {
        return -1;
    }

    *average = ((long double)limit + 1.0L) / 2.0L;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    unsigned long long limit;
    long double average;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0') {
        size_t length = 0;

        while (length < sizeof input && input[length] != '\0' &&
               input[length] != '\n') {
            ++length;
        }

        if (length == sizeof input || input[length] != '\n') {
            /* Possible weaknesses found:
             *  The scope of the variable 'ch' can be reduced. [variableScope]
             */
            int ch;

            if (!feof(stdin)) {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                while ((ch = getchar()) != '\n' && ch != EOF) {
                }
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    errno = 0;
    end = NULL;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (average_of_odds(limit, &average) != 0) {
        fputs("Enter a positive odd number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Average: %.2Lf\n", average);
    return EXIT_SUCCESS;
}