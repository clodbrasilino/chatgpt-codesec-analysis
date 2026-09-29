#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int average_even_numbers(unsigned long long limit,
                                long double *average)
{
    if (average == NULL || limit < 2ULL || limit % 2ULL != 0ULL) {
        return 0;
    }

    *average = ((long double)limit + 2.0L) / 2.0L;
    return 1;
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

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!average_even_numbers(limit, &average)) {
        fputs("Enter an even number greater than or equal to 2.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Average: %Lg\n", average) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}