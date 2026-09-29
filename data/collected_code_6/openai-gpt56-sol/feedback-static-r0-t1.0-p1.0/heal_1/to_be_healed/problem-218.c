#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long minimum_operations(long long first, long long second)
{
    if (first >= second) {
        return (unsigned long long)first - (unsigned long long)second;
    }

    return (unsigned long long)second - (unsigned long long)first;
}

static int parse_long_long(const char *text, long long *value)
{
    char *end = NULL;

    errno = 0;
    const long long parsed = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first_input[128];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second_input[128];
    long long first;
    long long second;

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%127s %127s", first_input, second_input) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_long_long(first_input, &first) ||
        !parse_long_long(second_input, &second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}