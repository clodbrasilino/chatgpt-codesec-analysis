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

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;
    char *end;
    unsigned long long n;
    unsigned long long sum;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_input;
        size_t new_capacity;

        if (length == SIZE_MAX - 1U) {
            free(input);
            fputs("Input too long\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    fputs("Input too long\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Memory allocation error\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0U && ch == EOF) {
        free(input);
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1U > capacity) {
        char *new_input = realloc(input, length + 1U);

        if (new_input == NULL) {
            free(input);
            fputs("Memory allocation error\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    errno = 0;
    n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!sum_even_squares(n, &sum)) {
        fputs("Result overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}