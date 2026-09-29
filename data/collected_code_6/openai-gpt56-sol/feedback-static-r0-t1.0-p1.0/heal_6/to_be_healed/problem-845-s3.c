#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int factorial_digit_count(unsigned long long n,
                                  unsigned long long *count)
{
    long double logarithm;

    if (count == NULL) {
        return -1;
    }

    if (n < 2ULL) {
        *count = 1ULL;
        return 0;
    }

    if ((long double)n > LDBL_MAX - 1.0L) {
        return -1;
    }

    errno = 0;
    logarithm = lgammal((long double)n + 1.0L) / logl(10.0L);

    if (errno != 0 || !isfinite(logarithm) || logarithm < 0.0L ||
        logarithm >= (long double)ULLONG_MAX) {
        return -1;
    }

    *count = (unsigned long long)floorl(logarithm) + 1ULL;
    return 0;
}

static int read_number(unsigned long long *value)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *start;
    char *parse_end;
    unsigned long long result;
    int status = -1;
    int ch;

    if (value == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            goto cleanup;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            goto cleanup;
        }
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = 1U;
    } else if (length == capacity) {
        char *new_input;

        if (capacity == SIZE_MAX) {
            goto cleanup;
        }

        new_input = realloc(input, capacity + 1U);
        if (new_input == NULL) {
            goto cleanup;
        }

        input = new_input;
        capacity++;
    }

    input[length] = '\0';
    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        goto cleanup;
    }

    errno = 0;
    result = strtoull(start, &parse_end, 10);

    if (errno == ERANGE || parse_end == start) {
        goto cleanup;
    }

    while (isspace((unsigned char)*parse_end)) {
        ++parse_end;
    }

    if (*parse_end != '\0') {
        goto cleanup;
    }

    *value = result;
    status = 0;

cleanup:
    free(input);
    return status;
}

int main(void)
{
    unsigned long long n;
    unsigned long long digits;

    if (read_number(&n) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (factorial_digit_count(n, &digits) != 0) {
        fputs("Unable to calculate digit count\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", digits) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}