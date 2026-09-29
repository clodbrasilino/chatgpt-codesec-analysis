#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_odd_naturals(uint64_t l, uint64_t r, uint64_t *result)
{
    if (result == NULL || l < 1U || l > r) {
        return 0;
    }

    uint64_t first = (l & 1U) != 0U ? l : l + 1U;
    uint64_t last = (r & 1U) != 0U ? r : r - 1U;

    if (first > last) {
        *result = 0U;
        return 1;
    }

    uint64_t count = ((last - first) / 2U) + 1U;
    uint64_t factor = first + count - 1U;

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

    if (!sum_odd_naturals(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}