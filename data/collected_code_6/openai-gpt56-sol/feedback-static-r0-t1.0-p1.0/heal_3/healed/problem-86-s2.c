#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int centered_hexagonal_number(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n == UINT64_C(0)) {
        return 0;
    }

    a = n;
    b = n - UINT64_C(1);

    if ((a & UINT64_C(1)) == UINT64_C(0)) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (b > (UINT64_MAX - UINT64_C(1)) / UINT64_C(6) / a) {
        return 0;
    }

    *result = UINT64_C(6) * a * b + UINT64_C(1);
    return 1;
}

int main(int argc, const char *const argv[])
{
    char *end;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == UINTMAX_C(0) || input > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!centered_hexagonal_number((uint64_t)input, &result)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}