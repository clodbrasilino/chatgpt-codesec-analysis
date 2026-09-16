#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int hexagonal_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n > UINT64_MAX / UINT64_C(2)) {
        return -1;
    }

    const uint64_t factor = (UINT64_C(2) * n) - UINT64_C(1);

    if (n != UINT64_C(0) && factor > UINT64_MAX / n) {
        return -1;
    }

    *result = n * factor;
    return 0;
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == UINTMAX_C(0) || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result = UINT64_C(0);

    if (hexagonal_number((uint64_t)input, &result) != 0) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}