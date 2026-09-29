#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int64_t sum_even_in_range(int64_t l, int64_t r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 1;
    }
    if (l % 2 != 0) {
        if (l == INT64_MAX) {
            return 0;
        }
        l++;
    }
    if (r % 2 != 0) {
        if (r == INT64_MIN) {
            return 0;
        }
        r--;
    }
    if (l > r) {
        return 0;
    }
    int64_t n = (r - l) / 2 + 1;
    int64_t first = l;
    int64_t last = r;
    int64_t sum_first_last = first + last;

    int64_t overflow_check_first_last = first + last;
    if (first > 0 && last > 0 && overflow_check_first_last < 0) {
        if (n % 2 == 0) {
            int64_t half_n = n / 2;
            int64_t half_first = first / 2;
            int64_t half_last = last / 2;
            int64_t remainder = (first % 2 + last % 2) / 2;
            if (half_n > INT64_MAX / 2) {
                int64_t half_result = half_n * half_first + half_n * half_last;
                if ((first % 2 != 0 && half_n > INT64_MAX - half_result) ||
                    (last % 2 != 0 && half_n > INT64_MAX - half_result)) {
                    return (first > 0) ? INT64_MAX : INT64_MIN;
                }
                return half_result + half_n * remainder;
            }
            int64_t half_sum = half_first + half_last;
            if (half_n > INT64_MAX / half_sum || half_n < INT64_MIN / half_sum) {
                return (first > 0) ? INT64_MAX : INT64_MIN;
            }
            int64_t result = half_n * half_sum;
            if (remainder != 0 && half_n > INT64_MAX - result) {
                return (first > 0) ? INT64_MAX : INT64_MIN;
            }
            return result + half_n * remainder;
        } else {
            int64_t half_sum = sum_first_last / 2;
            if (half_sum == 0) {
                return 0;
            }
            if (n > INT64_MAX / half_sum || n < INT64_MIN / half_sum) {
                return (first > 0) ? INT64_MAX : INT64_MIN;
            }
            return n * half_sum;
        }
    }
    if (first < 0 && last < 0 && overflow_check_first_last > 0) {
        if (n % 2 == 0) {
            int64_t half_n = n / 2;
            int64_t half_first = first / 2;
            int64_t half_last = last / 2;
            int64_t remainder = (first % 2 + last % 2) / 2;
            if (half_n < INT64_MIN / 2) {
                int64_t half_result = half_n * half_first + half_n * half_last;
                if ((first % 2 != 0 && half_n < INT64_MIN - half_result) ||
                    (last % 2 != 0 && half_n < INT64_MIN - half_result)) {
                    return (first > 0) ? INT64_MAX : INT64_MIN;
                }
                return half_result + half_n * remainder;
            }
            int64_t half_sum = half_first + half_last;
            if (half_n > INT64_MAX / half_sum || half_n < INT64_MIN / half_sum) {
                return (first > 0) ? INT64_MAX : INT64_MIN;
            }
            int64_t result = half_n * half_sum;
            if (remainder != 0 && half_n < INT64_MIN - result) {
                return (first > 0) ? INT64_MAX : INT64_MIN;
            }
            return result + half_n * remainder;
        } else {
            int64_t half_sum = sum_first_last / 2;
            if (half_sum == 0) {
                return 0;
            }
            if (n > INT64_MAX / half_sum || n < INT64_MIN / half_sum) {
                return (first > 0) ? INT64_MAX : INT64_MIN;
            }
            return n * half_sum;
        }
    }
    if (n % 2 == 0) {
        int64_t half_n = n / 2;
        if (half_n > INT64_MAX / sum_first_last || half_n < INT64_MIN / sum_first_last) {
            return (first > 0) ? INT64_MAX : INT64_MIN;
        }
        return half_n * sum_first_last;
    } else {
        int64_t half_sum = sum_first_last / 2;
        if (half_sum == 0) {
            return 0;
        }
        if (n > INT64_MAX / half_sum || n < INT64_MIN / half_sum) {
            return (first > 0) ? INT64_MAX : INT64_MIN;
        }
        return n * half_sum;
    }
}

int main(void) {
    long long l, r;
    printf("Enter lower bound: ");
    if (scanf("%lld", &l) != 1) {
        return 1;
    }
    printf("Enter upper bound: ");
    if (scanf("%lld", &r) != 1) {
        return 1;
    }
    long long result = sum_even_in_range(l, r);
    printf("Sum of even numbers in range [%lld, %lld]: %lld\n", l, r, result);
    return 0;
}