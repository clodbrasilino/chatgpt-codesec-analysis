#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

static int sum_odd_squares(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;

    if (result == NULL || n > UINT64_C(1903309)) {
        return 0;
    }

    a = n;
    b = UINT64_C(2) * n - UINT64_C(1);
    c = UINT64_C(2) * n + UINT64_C(1);

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    a *= b;

    if (a != 0 && c > UINT64_MAX / a) {
        return 0;
    }

    *result = a * c;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    char *number_start;
    uintmax_t value;
    uint64_t result;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0') {
        size_t length = 0;

        while (input[length] != '\0') {
            ++length;
        }

        if (length > 0 && input[length - 1] != '\n' && !feof(stdin)) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    end = input;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '-' || *end == '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    number_start = end;
    errno = 0;
    value = strtoumax(number_start, &end, 10);

    if (errno == ERANGE || end == number_start || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_squares((uint64_t)value, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}