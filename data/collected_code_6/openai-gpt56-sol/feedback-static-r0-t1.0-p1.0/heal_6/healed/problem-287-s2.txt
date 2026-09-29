#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>

static int sum_even_squares(unsigned long long n,
                            unsigned long long *result)
{
    unsigned long long a;
    unsigned long long b;
    unsigned long long c;

    if (result == NULL || n > (ULLONG_MAX - 1ULL) / 2ULL) {
        return 0;
    }

    a = n;
    b = n + 1ULL;
    c = 2ULL * n + 1ULL;

    if (a % 2ULL == 0ULL) {
        a /= 2ULL;
    } else {
        b /= 2ULL;
    }

    if (a % 3ULL == 0ULL) {
        a /= 3ULL;
    } else if (b % 3ULL == 0ULL) {
        b /= 3ULL;
    } else {
        c /= 3ULL;
    }

    if (a != 0ULL && b > ULLONG_MAX / a) {
        return 0;
    }
    a *= b;

    if (a != 0ULL && c > ULLONG_MAX / a) {
        return 0;
    }
    a *= c;

    if (a > ULLONG_MAX / 4ULL) {
        return 0;
    }

    *result = 4ULL * a;
    return 1;
}

static int read_number(unsigned long long *value)
{
    char buffer[256];
    char *end;
    unsigned long long parsed;
    size_t length;
    int ch;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    length = 0U;
    while (length < sizeof buffer && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == sizeof buffer || buffer[length] != '\n') {
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }
        return 0;
    }

    buffer[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtoull(buffer, &end, 10);

    if (errno == ERANGE || end == buffer) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    unsigned long long n;
    unsigned long long sum;

    if (!read_number(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_squares(n, &sum)) {
        fputs("Result overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}