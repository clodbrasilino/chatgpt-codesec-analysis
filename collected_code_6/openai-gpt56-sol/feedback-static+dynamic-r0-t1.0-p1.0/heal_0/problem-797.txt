#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_odd_naturals(int64_t l, int64_t r, uint64_t *result)
{
    uint64_t first;
    uint64_t last;
    uint64_t count;
    uint64_t half;

    if (result == NULL || l < 1 || r < l) {
        return 0;
    }

    first = (uint64_t)l;
    last = (uint64_t)r;

    if ((first & UINT64_C(1)) == 0U) {
        ++first;
    }

    if ((last & UINT64_C(1)) == 0U) {
        --last;
    }

    if (first > last) {
        *result = 0U;
        return 1;
    }

    count = ((last - first) / UINT64_C(2)) + UINT64_C(1);
    half = count / UINT64_C(2);

    if ((count & UINT64_C(1)) == 0U) {
        if (half != 0U && first + last > UINT64_MAX / half) {
            return 0;
        }
        *result = half * (first + last);
    } else {
        if (count != 0U && ((first + last) / UINT64_C(2)) > UINT64_MAX / count) {
            return 0;
        }
        *result = count * ((first + last) / UINT64_C(2));
    }

    return 1;
}

int main(void)
{
    int64_t l;
    int64_t r;
    uint64_t sum;

    if (scanf("%" SCNd64 " %" SCNd64, &l, &r) != 2) {
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