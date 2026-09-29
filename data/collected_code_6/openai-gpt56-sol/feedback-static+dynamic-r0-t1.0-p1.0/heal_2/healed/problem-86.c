#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int centered_hexagonal_number(uint64_t n, uint64_t *result)
{
    if (n == 0 || result == NULL) {
        return 0;
    }

    uint64_t a = n;
    uint64_t b = n - UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > (UINT64_MAX - UINT64_C(1)) / UINT64_C(6) / a) {
        return 0;
    }

    *result = UINT64_C(6) * a * b + UINT64_C(1);
    return 1;
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result;

    if (!centered_hexagonal_number((uint64_t)input, &result)) {
        fprintf(stderr, "Result is out of range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}