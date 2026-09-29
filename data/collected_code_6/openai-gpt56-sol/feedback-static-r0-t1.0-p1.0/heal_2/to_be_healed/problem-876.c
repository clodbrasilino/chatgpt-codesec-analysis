#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm(uintmax_t a, uintmax_t b, uintmax_t *result)
{
    uintmax_t divisor;

    if (a == 0 || b == 0 || result == NULL) {
        return -1;
    }

    divisor = gcd(a, b);

    if (a / divisor > UINTMAX_MAX / b) {
        return -1;
    }

    *result = (a / divisor) * b;
    return 0;
}

static int parse_uintmax(const char **input, uintmax_t *value)
{
    char *end;
    const char *start;

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    start = *input;

    if (*start == '\0' || *start == '-' || *start == '+') {
        return -1;
    }

    errno = 0;
    *value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE) {
        return -1;
    }

    *input = end;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    const char *cursor;
    uintmax_t a;
    uintmax_t b;
    uintmax_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    cursor = input;

    if (parse_uintmax(&cursor, &a) != 0 ||
        parse_uintmax(&cursor, &b) != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || a == 0 || b == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (lcm(a, b, &result) != 0) {
        fprintf(stderr, "LCM cannot be represented\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", result);
    return EXIT_SUCCESS;
}