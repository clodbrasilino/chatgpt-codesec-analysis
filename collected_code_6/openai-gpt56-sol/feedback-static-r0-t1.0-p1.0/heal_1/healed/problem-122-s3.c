#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_smart_number(uint64_t value)
{
    uint64_t low = 1;
    uint64_t high = value;

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;
        uint64_t quotient = value / mid;

        if (mid == quotient && value % mid == 0) {
            return 1;
        }

        if (mid > quotient) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return 0;
}

static int find_nth_smart_number(uint64_t n, uint64_t *result)
{
    uint64_t low;
    uint64_t high;

    if (n == 0 || result == NULL) {
        return 0;
    }

    low = 1;
    high = n;

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;
        uint64_t count = mid;

        if (is_smart_number(mid)) {
            --count;
        }

        if (count >= n) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    *result = low;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t parsed;

    if (value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line || parsed == 0 ||
        parsed > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    if (!read_uint64(&n)) {
        return EXIT_FAILURE;
    }

    if (!find_nth_smart_number(n, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}