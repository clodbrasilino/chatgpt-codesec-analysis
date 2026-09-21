#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>

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

    int64_t n = (r - l) / 2 + 1;

    if (n % 2 == 0) {
        int64_t half_n = n / 2;
        bool safe = true;

        if (half_n > INT64_MAX / l) safe = false;
        else if (half_n < INT64_MIN / l) safe = false;
        if (half_n > INT64_MAX / r) safe = false;
        else if (half_n < INT64_MIN / r) safe = false;

        if (safe) {
            int64_t term1 = half_n * l;
            int64_t term2 = half_n * r;
            if ((term1 >= 0 && term2 > INT64_MAX - term1) ||
                (term1 < 0 && term2 < INT64_MIN - term1)) {
                safe = false;
            }
        }

        if (!safe) {
            int64_t mid_sum = l + r;
            if ((l > 0 && r > 0 && mid_sum < 0) ||
                (l < 0 && r < 0 && mid_sum > 0)) {
                int64_t half_sum1 = l / 2;
                int64_t half_sum2 = r / 2;
                if (n > INT64_MAX / half_sum1 || n < INT64_MIN / half_sum1) {
                    return n * half_sum1 + n * half_sum2;
                }
            }
            return half_n * l + half_n * r;
        }

        int64_t sum = l + r;
        if (half_n > 0 && sum < 0 && (l > 0 || r > 0)) {
            if (half_n > INT64_MAX / sum || half_n < INT64_MIN / sum) {
                return half_n * l + half_n * r;
            }
        }
        if (half_n < 0 && sum > 0 && (l < 0 || r < 0)) {
            return half_n * l + half_n * r;
        }

        return half_n * sum;
    } else {
        int64_t half_sum = (l + r) / 2;
        if (half_sum == 0) {
            return 0;
        }

        if (n > 0) {
            if (half_sum > 0 && half_sum > INT64_MAX / n) {
                uint64_t un = (uint64_t)n;
                uint64_t uabs = (uint64_t)half_sum;
                uint64_t product = un * uabs;
                if (product > (uint64_t)INT64_MAX) {
                    int64_t div_l = l / 2;
                    int64_t div_r = r / 2;
                    return n * div_l + n * div_r;
                }
            } else if (half_sum < 0 && half_sum < INT64_MIN / n) {
                uint64_t un = (uint64_t)n;
                int64_t abs_half_sum = -half_sum;
                uint64_t uabs = (uint64_t)abs_half_sum;
                uint64_t product = un * uabs;
                uint64_t max_neg = (uint64_t)INT64_MAX + 1;
                if (product > max_neg) {
                    int64_t div_l = l / 2;
                    int64_t div_r = r / 2;
                    return n * div_l + n * div_r;
                }
            }
        }

        return n * half_sum;
    }
}

int main(void) {
    int64_t l, r;
    char buf[128];

    printf("Enter the range l and r: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }

    if (sscanf(buf, "%" SCNd64 "%" SCNd64, &l, &r) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    int64_t result = sum_of_odd_numbers(l, r);
    printf("Sum of odd numbers in range [%" PRId64 ", %" PRId64 "] = %" PRId64 "\n", l, r, result);

    return 0;
}