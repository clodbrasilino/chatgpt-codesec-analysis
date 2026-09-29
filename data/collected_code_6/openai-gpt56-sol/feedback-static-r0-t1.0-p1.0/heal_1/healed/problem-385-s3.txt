#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int perrin(size_t n, uint64_t *result)
{
    uint64_t p0 = 3U;
    uint64_t p1 = 0U;
    uint64_t p2 = 2U;

    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = p0;
        return 1;
    }

    if (n == 1U) {
        *result = p1;
        return 1;
    }

    if (n == 2U) {
        *result = p2;
        return 1;
    }

    for (size_t i = 3U; i <= n; ++i) {
        uint64_t next;

        if (UINT64_MAX - p0 < p1) {
            return 0;
        }

        next = p0 + p1;
        p0 = p1;
        p1 = p2;
        p2 = next;
    }

    *result = p2;
    return 1;
}

int main(int argc, const char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative-index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fputs("Invalid index.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input > (uintmax_t)SIZE_MAX) {
        fputs("Invalid index.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!perrin((size_t)input, &result)) {
        fputs("The result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}