#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int decagonal_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > UINT64_MAX / UINT64_C(4)) {
        return 0;
    }

    const uint64_t factor = UINT64_C(4) * n - UINT64_C(3);

    if (n > UINT64_MAX / factor) {
        return 0;
    }

    *result = n * factor;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        const char *program = argc > 0 && argv != NULL && argv[0] != NULL
                                  ? argv[0]
                                  : "program";
        fprintf(stderr, "Usage: %s <positive integer>\n", program);
        return EXIT_FAILURE;
    }

    if (argv == NULL || argv[1] == NULL || argv[1][0] == '\0' ||
        argv[1][0] == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || errno != 0 || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t result = 0;

    if (!decagonal_number((uint64_t)input, &result)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}