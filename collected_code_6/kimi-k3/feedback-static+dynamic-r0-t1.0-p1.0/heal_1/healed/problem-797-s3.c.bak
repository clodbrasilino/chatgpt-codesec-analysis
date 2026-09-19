#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_odd_natural(int64_t l, int64_t r) {
    if (l > r || r < 1) {
        return 0;
    }

    int64_t start = (l < 1) ? 1 : l;
    int64_t first_odd = (start % 2 == 0) ? start + 1 : start;

    if (first_odd > r) {
        return 0;
    }

    int64_t last_odd = (r % 2 == 0) ? r - 1 : r;
    int64_t count = (last_odd - first_odd) / 2 + 1;

    int64_t result = 0;
    if (count % 2 == 0) {
        __int128 half_count = (__int128)count / 2;
        __int128 sum = (__int128)first_odd + last_odd;
        __int128 product = half_count * sum;
        if (product > INT64_MAX) {
            return INT64_MAX;
        }
        result = (int64_t)product;
    } else {
        __int128 half_sum = ((__int128)first_odd + last_odd) / 2;
        __int128 product = half_sum * count;
        if (product > INT64_MAX) {
            return INT64_MAX;
        }
        result = (int64_t)product;
    }

    return result;
}

int main(void) {
    int64_t l, r;

    if (scanf("%" SCNd64 " %" SCNd64, &l, &r) != 2) {
        return 1;
    }

    printf("%" PRId64 "\n", sum_odd_natural(l, r));

    return 0;
}