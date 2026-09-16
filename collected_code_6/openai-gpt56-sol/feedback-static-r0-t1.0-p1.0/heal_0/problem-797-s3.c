#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_odd_natural_numbers(uint64_t l, uint64_t r, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t factor;

    if (result == NULL || l == 0U || l > r) {
        return 0;
    }

    first = l | UINT64_C(1);
    last = (r & UINT64_C(1)) != 0U ? r : r - UINT64_C(1);

    if (first > last) {
        *result = 0U;
        return 1;
    }

    count = ((last - first) / UINT64_C(2)) + UINT64_C(1);
    factor = (first / UINT64_C(2)) + (last / UINT64_C(2)) + UINT64_C(1);

    if (count != 0U && factor > UINT64_MAX / count) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

int main(void)
{
    uint64_t l;
    uint64_t r;
    uint64_t sum;

    if (scanf("%" SCNu64 " %" SCNu64, &l, &r) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!sum_odd_natural_numbers(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}