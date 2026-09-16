#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_max_equilateral_triangles(uint64_t side, uint64_t *result)
{
    if (result == NULL || side == 0 || side > UINT64_MAX / side) {
        return 0;
    }

    *result = side * side;
    return 1;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side-length-ratio>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
        fputs("Invalid side-length ratio\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_max_equilateral_triangles((uint64_t)input, &result)) {
        fputs("Result cannot be represented\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}