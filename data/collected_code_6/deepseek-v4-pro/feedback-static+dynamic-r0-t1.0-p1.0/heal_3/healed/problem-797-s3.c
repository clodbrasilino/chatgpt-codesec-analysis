#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_of_odd_numbers(int64_t l, int64_t r) {
    if (l > r) {
        return 0;
    }

    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }

    if (l > r) {
        return 0;
    }

    int64_t n = (r - l) / 2 + 1;

    if (n % 2 == 0) {
        int64_t half_n = n / 2;
        if (half_n > 0) {
            if (l > INT64_MAX - r) {
                return half_n * l + half_n * r;
            }
            int64_t sum = l + r;
            if (sum < 0 && half_n > 0) {
                if (sum < INT64_MIN / half_n) {
                    return half_n * l + half_n * r;
                }
            }
            return half_n * sum;
        }
        return half_n * (l + r);
    } else {
        int64_t half_sum = (l + r) / 2;
        if (half_sum == 0) {
            return 0;
        }
        if (n > 0) {
            if (half_sum > INT64_MAX / n || half_sum < INT64_MIN / n) {
                uint64_t un = (uint64_t)n;
                int64_t result_sign = 1;
                int64_t abs_half_sum = half_sum;
                if (half_sum < 0) {
                    result_sign = -1;
                    abs_half_sum = -half_sum;
                }
                uint64_t uabs = (uint64_t)abs_half_sum;
                uint64_t product = un * uabs;
                if (result_sign < 0) {
                    if (product > (uint64_t)INT64_MAX + 1) {
                        return n * half_sum;
                    }
                } else {
                    if (product > (uint64_t)INT64_MAX) {
                        return n * half_sum;
                    }
                }
            }
        }
        return n * half_sum;
    }
}

int main(void) {
    int64_t l, r;
    char buf[64];
    printf("Enter the range l and r: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    if (sscanf(buf, "%" SCNd64 " %" SCNd64, &l, &r) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    int64_t result = sum_of_odd_numbers(l, r);
    printf("Sum of odd numbers in range [%" PRId64 ", %" PRId64 "] = %" PRId64 "\n", l, r, result);

    return 0;
}