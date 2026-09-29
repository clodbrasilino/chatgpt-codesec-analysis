#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_ways(size_t n, uint64_t k, uint64_t *result)
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

    for (size_t i = 3; i <= n; ++i) {
        if (same > UINT64_MAX - different) {
            return 0;
        }

        uint64_t total = same + different;

        if (k > 1 && total > UINT64_MAX / (k - 1)) {
            return 0;
        }

        same = different;
        different = total * (k - 1);
    }

    if (same > UINT64_MAX - different) {
        return 0;
    }

    *result = same + different;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *cursor;
    char *end;
    uintmax_t n_value;
    uintmax_t k_value;
    size_t n;
    uint64_t k;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    errno = 0;
    n_value = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || n_value == 0 ||
        n_value > SIZE_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = end;
    errno = 0;
    k_value = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || k_value == 0 ||
        k_value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    n = (size_t)n_value;
    k = (uint64_t)k_value;

    if (!count_ways(n, k, &result)) {
        fputs("Invalid input or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}