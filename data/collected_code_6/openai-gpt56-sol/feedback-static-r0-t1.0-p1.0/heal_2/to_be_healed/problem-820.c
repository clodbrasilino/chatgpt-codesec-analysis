#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int month_has_28_days(int month)
{
    return month == 2;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *end;
    long month;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (input[0] != '\0') {
        size_t length = 0;

        while (input[length] != '\0') {
            ++length;
        }

        if (length == sizeof input - 1 && input[length - 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    month = strtol(input, &end, 10);

    if (errno != 0 || end == input || month < 1 || month > 12) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(month_has_28_days((int)month) ? "Yes" : "No");
    return EXIT_SUCCESS;
}