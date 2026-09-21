#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_even_natural_numbers(uint64_t left, uint64_t right, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t half;
    uint64_t factor;

    if (result == NULL || left == 0 || left > right) {
        return 0;
    }

    first = left + (left & UINT64_C(1));
    last = right - (right & UINT64_C(1));

    if (first > right || first > last) {
        *result = 0;
        return 1;
    }

    count = ((last - first) / UINT64_C(2)) + UINT64_C(1);

    if ((count & UINT64_C(1)) == 0) {
        half = count / UINT64_C(2);
        factor = first + last;
    } else {
        half = (first + last) / UINT64_C(2);
        factor = count;
    }

    if (half != 0 && factor > UINT64_MAX / half) {
        return 0;
    }

    *result = half * factor;
    return 1;
}

static int read_range(uint64_t *left, uint64_t *right)
{
    char buffer[256];
    char extra;
    int matched;

    if (left == NULL || right == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    matched = sscanf(buffer, "%" SCNu64 " %" SCNu64 " %c", left, right, &extra);

    return errno != ERANGE && matched == 2;
}

int main(void)
{
    uint64_t left;
    uint64_t right;
    uint64_t sum;

    if (!read_range(&left, &right)) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!sum_even_natural_numbers(left, right, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}