#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int sum_even_squares(unsigned long long n, unsigned long long *result)
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
    char input[128];
    char *end;
    int ch;

    if (value == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    for (end = input; *end != '\0' && *end != '\n'; ++end) {
    }

    if (*end == '\n') {
        *end = '\0';
    } else if (!feof(stdin)) {
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }
        return 0;
    }

    errno = 0;
    end = NULL;
    *value = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    return *end == '\0';
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