#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_of_odd_numbers(int64_t l, int64_t r) {
    if (l > r) {
        return 0;
    }

    if (l % 2 == 0) {
        if (l == INT64_MAX) {
            return 0;
        }
        l++;
    }
    if (r % 2 == 0) {
        if (r == INT64_MIN) {
            return 0;
        }
        r--;
    }

    if (l > r) {
        return 0;
    }

    uint64_t range = (uint64_t)(r - l);
    int64_t n = (int64_t)(range / 2 + 1);

    if (n % 2 == 0) {
        return (int64_t)((n / 2) * ((uint64_t)l + (uint64_t)r));
    } else {
        return (int64_t)((uint64_t)n * ((uint64_t)(l + r) / 2));
    }
}

int main(void) {
    int64_t l, r;
    printf("Enter the range l and r: ");
    if (scanf("%" SCNd64 " %" SCNd64, &l, &r) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    int64_t result = sum_of_odd_numbers(l, r);
    printf("Sum of odd numbers in range [%" PRId64 ", %" PRId64 "] = %" PRId64 "\n", l, r, result);

    return 0;
}