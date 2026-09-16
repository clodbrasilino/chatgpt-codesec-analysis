#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int star_number(uint64_t n, uint64_t *result)
{
    const uint64_t max_n = UINT64_C(1753413056);

    if (result == NULL || n == 0 || n > max_n) {
        return 0;
    }

    *result = UINT64_C(6) * n * (n - UINT64_C(1)) + UINT64_C(1);
    return 1;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!star_number((uint64_t)input, &result)) {
        fprintf(stderr, "Input is outside the supported range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}