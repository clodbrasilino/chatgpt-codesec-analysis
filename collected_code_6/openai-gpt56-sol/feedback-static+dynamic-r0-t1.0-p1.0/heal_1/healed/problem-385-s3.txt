#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int perrin(size_t n, uint64_t *result)
{
    uint64_t p0 = UINT64_C(3);
    uint64_t p1 = UINT64_C(0);
    uint64_t p2 = UINT64_C(2);

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

int main(int argc, char *const argv[])
{
    char *end;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative-index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > SIZE_MAX) {
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