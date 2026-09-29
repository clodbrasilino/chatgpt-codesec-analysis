#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_tilings(size_t n, uint64_t *result)
{
    uint64_t previous = UINT64_C(1);
    uint64_t current = UINT64_C(3);

    if (result == NULL) {
        return -1;
    }

    if ((n & 1U) != 0U) {
        *result = UINT64_C(0);
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 0;
    }

    for (size_t width = 4U; width <= n;) {
        if (current > UINT64_MAX / UINT64_C(4) ||
            UINT64_C(4) * current < previous) {
            return -1;
        }

        uint64_t next = UINT64_C(4) * current - previous;
        previous = current;
        current = next;

        if (n - width < 2U) {
            break;
        }

        width += 2U;
    }

    *result = current;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    ssize_t length;
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno != 0 || end == input || parsed > SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (count_tilings((size_t)parsed, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}