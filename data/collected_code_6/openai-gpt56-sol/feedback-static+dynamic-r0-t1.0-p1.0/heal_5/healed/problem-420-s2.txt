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

int main(void)
{
    char input[256];
    char *end;
    uintmax_t parsed;
    uint64_t result;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Invalid input.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_sum_even((uint64_t)parsed, &result) != 0) {
        fputs("Result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}