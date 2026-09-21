#include <errno.h>
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
    char *end;
    long long parsed;

    errno = 0;
    parsed = strtoll(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    long long first;
    long long second;
    char extra;
    int result = EXIT_FAILURE;

    if (getline(&line, &capacity, stdin) < 0) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char first_input[32];
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char second_input[32];

        /* Possible weaknesses found:
         * Flawfinder sscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
         */
        if (sscanf(line, " %31s %31s %c",
                   first_input, second_input, &extra) != 2 ||
            !parse_long_long(first_input, &first) ||
            !parse_long_long(second_input, &second)) {
            fputs("Invalid input\n", stderr);
            goto cleanup;
        }
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(line);
    return result;
}