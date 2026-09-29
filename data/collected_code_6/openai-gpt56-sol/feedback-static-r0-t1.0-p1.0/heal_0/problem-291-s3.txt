#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_painting_ways(uint64_t n, uint64_t k, uint64_t *result)
{
    if (result == NULL || n == 0 || k == 0) {
        return 0;
    }

    if (n == 1) {
        *result = k;
        return 1;
    }

    if (k > UINT64_MAX / k) {
        return 0;
    }

    uint64_t same = k;
    uint64_t different = k * (k - 1);

    for (uint64_t i = 3; i <= n; ++i) {
        if (same > UINT64_MAX - different) {
            return 0;
        }

        uint64_t total = same + different;

        if (k - 1 != 0 && total > UINT64_MAX / (k - 1)) {
            return 0;
        }

        uint64_t next_same = different;
        uint64_t next_different = total * (k - 1);

        same = next_same;
        different = next_different;
    }

    if (same > UINT64_MAX - different) {
        return 0;
    }

    *result = same + different;
    return 1;
}

static int read_uint64(const char *text, uint64_t *value)
{
    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <posts> <colors>\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint64_t n = 0;
    uint64_t k = 0;
    uint64_t ways = 0;

    if (!read_uint64(argv[1], &n) || !read_uint64(argv[2], &k) ||
        n == 0 || k == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_painting_ways(n, k, &ways)) {
        fputs("Result exceeds uint64_t range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", ways);
    return EXIT_SUCCESS;
}