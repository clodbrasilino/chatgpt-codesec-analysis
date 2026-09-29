#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int first_factorial_digit(unsigned long long n)
{
    if (n < 2ULL) {
        return 1;
    }

    long double logarithm =
        lgammal((long double)n + 1.0L) / logl(10.0L);

    if (!isfinite(logarithm)) {
        return -1;
    }

    long double fractional_part = logarithm - floorl(logarithm);
    long double leading = powl(10.0L, fractional_part);
    int digit = (int)floorl(leading);

    if (digit < 1) {
        return 1;
    }

    return digit > 9 ? 9 : digit;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (!feof(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    char *cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long n = strtoull(cursor, &end, 10);

    if (errno == ERANGE || end == cursor) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    int digit = first_factorial_digit(n);
    free(input);

    if (digit < 0 || printf("%d\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}