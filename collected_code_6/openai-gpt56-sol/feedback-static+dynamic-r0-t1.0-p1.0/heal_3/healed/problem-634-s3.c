#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers_of_evens(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t even;
        uint64_t square;
        uint64_t fourth;

        if (i > UINT64_MAX / UINT64_C(2)) {
            return -1;
        }

        even = i * UINT64_C(2);

        if (even != 0 && even > UINT64_MAX / even) {
            return -1;
        }

        square = even * even;

        if (square != 0 && square > UINT64_MAX / square) {
            return -1;
        }

        fourth = square * square;

        if (sum > UINT64_MAX - fourth) {
            return -1;
        }

        sum += fourth;
    }

    *result = sum;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;
    int ch;
    int first = 1;
    int saw_digit = 0;
    int overflow = 0;

    if (value == NULL) {
        return -1;
    }

    parsed = 0;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        unsigned int digit;

        if (first) {
            while (ch != '\n' && ch != EOF &&
                   isspace((unsigned char)ch)) {
                ch = getchar();
            }

            if (ch == '+') {
                ch = getchar();
            } else if (ch == '-') {
                overflow = 1;
            }

            first = 0;

            if (ch == '\n' || ch == EOF) {
                break;
            }
        }

        if (isdigit((unsigned char)ch)) {
            digit = (unsigned int)(ch - '0');
            saw_digit = 1;

            if (parsed > (UINT64_MAX - digit) / UINTMAX_C(10)) {
                overflow = 1;
            } else if (!overflow) {
                parsed = parsed * UINTMAX_C(10) + digit;
            }
        } else if (isspace((unsigned char)ch)) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
                if (!isspace((unsigned char)ch)) {
                    overflow = 1;
                }
            }
            break;
        } else {
            overflow = 1;
        }
    }

    if (ferror(stdin) || !saw_digit || overflow) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    errno = 0;

    if (read_uint64(&n) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_fourth_powers_of_evens(n, &result) != 0) {
        fputs("Result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}