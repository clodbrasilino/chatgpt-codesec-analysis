#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
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
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *end;
    unsigned long long parsed;
    int ch;

    if (value == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length + 1U >= capacity) {
            if (capacity == 0U) {
                new_capacity = 32U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(line);
                    return 0;
                }
                new_capacity = capacity * 2U;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return 0;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0U)) {
        free(line);
        return 0;
    }

    if (length + 1U >= capacity) {
        char *resized;

        if (length == SIZE_MAX) {
            free(line);
            return 0;
        }

        resized = realloc(line, length + 1U);
        if (resized == NULL) {
            free(line);
            return 0;
        }

        line = resized;
    }

    line[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtoull(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    free(line);
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