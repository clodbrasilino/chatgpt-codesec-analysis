#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <ctype.h>

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n == UINT64_MAX) {
        return -1;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return -1;
    }

    a *= b;

    if (a != 0 && a > UINT64_MAX / a) {
        return -1;
    }

    a *= a;

    if (a > UINT64_MAX / UINT64_C(2)) {
        return -1;
    }

    *result = UINT64_C(2) * a;
    return 0;
}

static int read_number(uint64_t *value)
{
    uintmax_t parsed;
    uint64_t converted;
    int ch;
    int saw_digit = 0;
    int overflow = 0;
    int trailing = 0;

    if (value == NULL) {
        return -1;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return ferror(stdin) ? -2 : -3;
        }
    } while (isspace((unsigned char)ch) && ch != '\n');

    if (ch == '\n' || ch == '-') {
        while (ch != '\n' && ch != EOF) {
            ch = fgetc(stdin);
        }
        return ch == EOF && ferror(stdin) ? -2 : -3;
    }

    parsed = 0;

    while (ch != EOF && isdigit((unsigned char)ch)) {
        unsigned int digit = (unsigned int)(ch - '0');

        saw_digit = 1;
        if (parsed > (UINTMAX_MAX - digit) / UINTMAX_C(10)) {
            overflow = 1;
        } else if (!overflow) {
            parsed = parsed * UINTMAX_C(10) + digit;
        }

        ch = fgetc(stdin);
    }

    while (ch != '\n' && ch != EOF) {
        if (!isspace((unsigned char)ch)) {
            trailing = 1;
        }
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        return -2;
    }

    if (!saw_digit || overflow || trailing || parsed > UINT64_MAX) {
        return -3;
    }

    converted = (uint64_t)parsed;
    *value = converted;
    return 0;
}

int main(void)
{
    uint64_t input;
    uint64_t result;
    int status;

    status = read_number(&input);
    if (status != 0) {
        if (status == -2) {
            fputs("Failed to read input.\n", stderr);
        } else if (status == -1) {
            fputs("Unable to store input.\n", stderr);
        } else {
            fputs("Invalid input.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (cube_sum_even(input, &result) != 0) {
        fputs("Result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}