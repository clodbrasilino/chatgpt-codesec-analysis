#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_odd_natural_numbers(uint64_t l, uint64_t r, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t factor;

    if (result == NULL || l == 0 || l > r) {
        return 0;
    }

    first = l | UINT64_C(1);
    last = (r & UINT64_C(1)) != 0 ? r : r - UINT64_C(1);

    if (first > last) {
        *result = 0;
        return 1;
    }

    count = ((last - first) / UINT64_C(2)) + UINT64_C(1);
    factor = (first / UINT64_C(2)) + (last / UINT64_C(2)) + UINT64_C(1);

    if (factor > UINT64_MAX / count) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

static int read_range(uint64_t *l, uint64_t *r)
{
    char buffer[256];
    char *cursor;
    char *end;

    if (l == NULL || r == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    cursor = buffer;
    errno = 0;
    *l = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || *l > UINT64_MAX) {
        return 0;
    }

    cursor = end;
    errno = 0;
    *r = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || *r > UINT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    return *end == '\0';
}

int main(void)
{
    uint64_t l;
    uint64_t r;
    uint64_t sum;

    if (!read_range(&l, &r)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_odd_natural_numbers(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}