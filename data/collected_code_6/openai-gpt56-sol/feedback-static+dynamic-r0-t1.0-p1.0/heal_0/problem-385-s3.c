#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int perrin(size_t n, uint64_t *result)
{
    uint64_t first;
    uint64_t second;

    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = 3U;
        return 1;
    }

    if (n == 1U) {
        *result = 0U;
        return 1;
    }

    if (n == 2U) {
        *result = 2U;
        return 1;
    }

    if (!perrin(n - 2U, &first) || !perrin(n - 3U, &second)) {
        return 0;
    }

    if (UINT64_MAX - first < second) {
        return 0;
    }

    *result = first + second;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative-index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || input > SIZE_MAX) {
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