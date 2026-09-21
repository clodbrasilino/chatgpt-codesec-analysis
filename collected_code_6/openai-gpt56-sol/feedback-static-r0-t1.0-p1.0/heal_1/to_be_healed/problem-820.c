#include <errno.h>
#include <limits.h>
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

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
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

    printf("%s\n", month_has_28_days((int)month) ? "Yes" : "No");
    return EXIT_SUCCESS;
}