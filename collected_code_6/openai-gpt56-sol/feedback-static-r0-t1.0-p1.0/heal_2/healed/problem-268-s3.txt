#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int star_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0) {
        return 0;
    }

    const uint64_t k = n - 1;

    if (k != 0 && k > UINT64_MAX / 6) {
        return 0;
    }

    const uint64_t six_k = 6 * k;

    if (six_k > (UINT64_MAX - 1) / (k + 1)) {
        return 0;
    }

    *result = six_k * (k + 1) + 1;
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
        fputs("Invalid positive integer\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t result;

    if (!star_number((uint64_t)input, &result)) {
        fputs("Star number exceeds the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}