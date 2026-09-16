#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int perrin(size_t n, uint64_t *value)
{
    uint64_t p0 = 3;
    uint64_t p1 = 0;
    uint64_t p2 = 2;

    if (value == NULL) {
        return 0;
    }

    if (n == 0) {
        *value = p0;
        return 1;
    }

    if (n == 1) {
        *value = p1;
        return 1;
    }

    if (n == 2) {
        *value = p2;
        return 1;
    }

    for (size_t i = 3; i <= n; ++i) {
        uint64_t next;

        if (UINT64_MAX - p0 < p1) {
            return 0;
        }

        next = p0 + p1;
        p0 = p1;
        p1 = p2;
        p2 = next;
    }

    *value = p2;
    return 1;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > SIZE_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!perrin((size_t)input, &result)) {
        fprintf(stderr, "Unable to calculate the Perrin number\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}