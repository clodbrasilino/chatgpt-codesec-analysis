#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nonagonal_number(uint64_t n, uint64_t *result)
{
    uint64_t factor;
    uint64_t a;
    uint64_t b;

    if (result == NULL || n == 0 || n > UINT64_MAX / 7) {
        return 0;
    }

    factor = 7 * n - 5;
    a = n;
    b = factor;

    if ((a & UINT64_C(1)) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a > UINT64_MAX / b) {
        return 0;
    }

    *result = a * b;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <positive integer>\n", program);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        end == NULL ||
        *end != '\0' ||
        parsed == 0 ||
        parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!nonagonal_number((uint64_t)parsed, &result)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}