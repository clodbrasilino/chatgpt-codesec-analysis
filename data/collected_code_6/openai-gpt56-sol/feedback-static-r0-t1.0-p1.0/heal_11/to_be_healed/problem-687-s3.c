#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    if (value >= 0) {
        return (uintmax_t)value;
    }

    return (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1);
}

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != UINTMAX_C(0)) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch != EOF || !ferror(stdin);
}

static int read_intmax(intmax_t *value)
{
    enum { INPUT_SIZE = 256 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[INPUT_SIZE];
    char *start;
    char *end;
    intmax_t parsed;
    size_t length;

    if (value == NULL) {
        return 0;
    }

    if (fgets(line, sizeof line, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < sizeof line && line[length] != '\0') {
        ++length;
    }

    if (length == sizeof line) {
        discard_line();
        return 0;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    } else if (!feof(stdin)) {
        discard_line();
        return 0;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
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
    intmax_t first;
    intmax_t second;
    uintmax_t result;

    if (!read_intmax(&first) || !read_intmax(&second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    result = gcd(magnitude(first), magnitude(second));

    if (printf("%" PRIuMAX "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}