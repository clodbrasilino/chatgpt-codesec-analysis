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
    char *input;
    char *end;
    unsigned long long parsed;
    size_t capacity;
    size_t length;
    int ch;

    if (value == NULL) {
        return 0;
    }

    capacity = 32U;
    length = 0U;
    input = malloc(capacity);

    if (input == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1U) {
            free(input);
            return 0;
        }

        if (length + 1U >= capacity) {
            char *expanded;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return 0;
            }

            new_capacity = capacity * 2U;
            expanded = realloc(input, new_capacity);

            if (expanded == NULL) {
                free(input);
                return 0;
            }

            input = expanded;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0U)) {
        free(input);
        return 0;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return 0;
    }

    *value = parsed;
    free(input);
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