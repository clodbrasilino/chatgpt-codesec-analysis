#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int decagonal_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > UINT64_MAX / 4) {
        return 0;
    }

    const uint64_t factor = 4 * n - 3;

    if (n > UINT64_MAX / factor) {
        return 0;
    }

    *result = n * factor;
    return 1;
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <positive integer>\n", program);
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL || argv[1][0] == '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid input\n");
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

    uint64_t result = 0;

    if (!decagonal_number((uint64_t)input, &result)) {
        fprintf(stderr, "Result is out of range\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}