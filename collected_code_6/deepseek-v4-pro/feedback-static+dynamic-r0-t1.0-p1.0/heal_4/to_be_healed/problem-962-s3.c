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
    int64_t sum_first_last;
    if ((first > 0 && last > INT64_MAX - first) || (first < 0 && last < INT64_MIN - first)) {
        if (n % 2 == 0) {
            int64_t half_n = n / 2;
            int64_t half_sum = first / 2 + last / 2;
            /* Possible weaknesses found:
             *  Variable 'remainder' is assigned a value that is never used. [unreadVariable]
             */
            int64_t remainder = (first % 2 + last % 2) / 2;
            if (half_n > INT64_MAX / 2) {
                int64_t half_result = half_n * (first / 2) + half_n * (last / 2);
                if ((first % 2 != 0 && half_n > INT64_MAX - half_result) ||
                    (last % 2 != 0 && half_n > INT64_MAX - half_result)) {
                    return (first > 0) ? INT64_MAX : INT64_MIN;
                }
                return half_result + half_n * ((first % 2 + last % 2) / 2);
            }
            if (half_n > INT64_MAX / half_sum || half_n < INT64_MIN / half_sum) {
                return (first > 0) ? INT64_MAX : INT64_MIN;
            }
            /* Possible weaknesses found:
             *  Uninitialized variable: sum_first_last [legacyUninitvar]
             */
            return half_n * sum_first_last;
        } else {
            /* Possible weaknesses found:
             *  Uninitialized variable: sum_first_last [uninitvar]
             */
            int64_t half_sum = sum_first_last / 2;
            /* Possible weaknesses found:
             * UBSan: division by zero (AFL crash: id:000000,sig:06,src:000001,time:3669,execs:2469,op:havoc,rep:4)
             */
            if (n > INT64_MAX / half_sum || n < INT64_MIN / half_sum) {
                return (first > 0) ? INT64_MAX : INT64_MIN;
            }
            return n * half_sum;
        }
    }
    sum_first_last = first + last;
    if (n % 2 == 0) {
        int64_t half_n = n / 2;
        if (half_n > INT64_MAX / sum_first_last || half_n < INT64_MIN / sum_first_last) {
            return (first > 0) ? INT64_MAX : INT64_MIN;
        }
        return half_n * sum_first_last;
    } else {
        int64_t half_sum = sum_first_last / 2;
        if (n > INT64_MAX / half_sum || n < INT64_MIN / half_sum) {
            return (first > 0) ? INT64_MAX : INT64_MIN;
        }
        return n * half_sum;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000007,time:18233,execs:12275,op:havoc,rep:2; likely memory-safety defect
  */

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