#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_nth_non_multiple(uint64_t n, uint64_t divisor,
                                 uint64_t *result)
{
    uint64_t quotient;
    uint64_t remainder;

    if (n == 0 || divisor <= 1 || result == NULL) {
        return 0;
    }

    quotient = (n - 1) / (divisor - 1);
    remainder = (n - 1) % (divisor - 1);

    if (remainder == UINT64_MAX ||
        quotient > (UINT64_MAX - remainder - 1) / divisor) {
        return 0;
    }

    *result = quotient * divisor + remainder + 1;
    return 1;
}

static int parse_uint64(const char **cursor, uint64_t *result)
{
    char *end;
    uintmax_t value;

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    if (**cursor == '\0' || **cursor == '+' || **cursor == '-') {
        return 0;
    }

    errno = 0;
    value = strtoumax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE || value > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)value;
    *cursor = end;
    return 1;
}

static int parse_input(uint64_t *n, uint64_t *divisor)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    const char *cursor;
    int valid;

    if (n == NULL || divisor == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    cursor = line;
    valid = parse_uint64(&cursor, n) &&
            parse_uint64(&cursor, divisor);

    while (valid && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    valid = valid && *cursor == '\0';

    free(line);
    return valid;
}

int main(void)
{
    uint64_t n;
    uint64_t divisor;
    uint64_t result;

    if (!parse_input(&n, &divisor)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_nth_non_multiple(n, divisor, &result)) {
        fputs("Unable to compute result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}