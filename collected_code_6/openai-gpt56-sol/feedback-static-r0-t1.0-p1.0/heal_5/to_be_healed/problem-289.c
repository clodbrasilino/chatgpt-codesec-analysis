#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int is_leap_year(long long year)
{
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

static int odd_days_in_year(long long year)
{
    return is_leap_year(year) ? 2 : 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    long long year;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the year.\n");
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fprintf(stderr, "Input is too long.\n");
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = NULL;
    year = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input || year <= 0) {
        fprintf(stderr, "Invalid year.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid year.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", odd_days_in_year(year));
    return EXIT_SUCCESS;
}