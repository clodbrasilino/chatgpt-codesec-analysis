#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t integer_sqrt(uint64_t value)
{
    uint64_t low = 0;
    uint64_t high = UINT32_MAX;
    uint64_t result = 0;

    if (value < high) {
        high = value;
    }

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;

        if (mid == 0 || mid <= value / mid) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

static uint64_t count_smart_numbers(uint64_t value)
{
    return value - integer_sqrt(value);
}

static int find_nth_smart_number(uint64_t n, uint64_t *result)
{
    uint64_t low;
    uint64_t high;

    if (n == 0 || result == NULL) {
        return 0;
    }

    low = n;

    if (n == UINT64_MAX) {
        high = UINT64_MAX;
    } else {
        uint64_t root = integer_sqrt(n);
        uint64_t extra = root + 2;

        high = n > UINT64_MAX - extra ? UINT64_MAX : n + extra;

        while (count_smart_numbers(high) < n) {
            uint64_t increment = high / 2 + 1;

            if (high > UINT64_MAX - increment) {
                high = UINT64_MAX;
                break;
            }

            high += increment;
        }
    }

    if (count_smart_numbers(high) < n) {
        return 0;
    }

    while (low < high) {
        uint64_t mid = low + (high - low) / 2;

        if (count_smart_numbers(mid) >= n) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    *result = low;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno != 0 || end == input || parsed == 0 || parsed > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (!find_nth_smart_number((uint64_t)parsed, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}