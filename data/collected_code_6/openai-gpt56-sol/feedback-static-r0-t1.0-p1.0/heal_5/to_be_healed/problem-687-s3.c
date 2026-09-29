#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    return value < 0
        ? (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1)
        : (uintmax_t)value;
}

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_intmax(intmax_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    size_t length = 0;
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    do {
        if (length + 1 >= sizeof token) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != EOF &&
                   !isspace((unsigned char)ch)) {
            }
            return 0;
        }

        token[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    token[length] = '\0';

    errno = 0;
    char *end;
    intmax_t parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int only_whitespace_remains(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    intmax_t first;
    intmax_t second;

    if (!read_intmax(&first) ||
        !read_intmax(&second) ||
        !only_whitespace_remains()) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n",
           gcd(magnitude(first), magnitude(second)));

    return EXIT_SUCCESS;
}