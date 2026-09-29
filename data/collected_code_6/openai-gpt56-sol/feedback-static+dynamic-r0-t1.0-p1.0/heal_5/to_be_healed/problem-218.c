#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long magnitude(long long value)
{
    if (value >= 0) {
        return (unsigned long long)value;
    }

    return 0ULL - (unsigned long long)value;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

static unsigned long long minimum_operations(long long first, long long second)
{
    unsigned long long difference;

    if (first >= second) {
        return (unsigned long long)first - (unsigned long long)second;
    }

    difference = (unsigned long long)second - (unsigned long long)first;

    if (first > 0) {
        return 1ULL + difference / 2ULL;
    }

    return magnitude(first) + 1ULL + (unsigned long long)second / 2ULL;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *cursor;
    char *end;
    long long first;
    long long second;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;
    errno = 0;
    first = strtoll(cursor, &end, 10);

    if (cursor == end || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = end;
    errno = 0;
    second = strtoll(cursor, &end, 10);

    if (cursor == end || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}