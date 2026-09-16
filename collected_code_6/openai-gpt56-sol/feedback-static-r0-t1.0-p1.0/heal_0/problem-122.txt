#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_smart_number(uint64_t value)
{
    uint64_t low = 0;
    uint64_t high = value < UINT32_MAX ? value : UINT32_MAX;

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;
        uint64_t square = mid * mid;

        if (square == value) {
            return 1;
        }

        if (square < value) {
            low = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        }
    }

    return 0;
}

static int find_nth_smart_number(uint64_t n, uint64_t *result)
{
    if (n == 0 || result == NULL || n - 1 > UINT32_MAX) {
        return 0;
    }

    *result = (n - 1) * (n - 1);
    return 1;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || parsed == 0 || parsed > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_nth_smart_number((uint64_t)parsed, &result) ||
        !is_smart_number(result)) {
        fputs("The requested smart number is out of range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}