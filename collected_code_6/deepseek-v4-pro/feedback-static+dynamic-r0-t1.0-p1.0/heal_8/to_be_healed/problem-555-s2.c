#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_of_cubes_minus_sum(int64_t n) {
    if (n < 1) {
        return 0;
    }
    
    int64_t sum;
    if (n % 2 == 0) {
        int64_t half_n = n / 2;
        if (half_n > INT64_MAX / (n + 1)) {
            return -1;
        }
        sum = half_n * (n + 1);
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:195,execs:128,op:havoc,rep:1)
         */
        int64_t half_n_plus_1 = (n + 1) / 2;
        if (half_n_plus_1 > INT64_MAX / n) {
            return -1;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 * -4611686018427387904 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:195,execs:128,op:havoc,rep:1)
         */
        sum = n * half_n_plus_1;
    }
    
    if (sum > INT64_MAX / sum) {
        int64_t sum_cubes = 0;
        for (int64_t i = 1; i <= n; i++) {
            if (i > INT64_MAX / i) {
                return -1;
            }
            int64_t i_squared = i * i;
            if (i_squared > INT64_MAX / i) {
                return -1;
            }
            int64_t term = i_squared * i;
            if (sum_cubes > INT64_MAX - term) {
                return -1;
            }
            sum_cubes += term;
        }
        if (sum_cubes < sum) {
            return -1;
        }
        return sum_cubes - sum;
    }
    
    int64_t sum_cubes = sum * sum;
    if (sum_cubes < sum) {
        return -1;
    }
    return sum_cubes - sum;
}

int main(void) {
    int64_t n;
    printf("Enter a positive integer: ");
    if (scanf("%" SCNd64, &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    int64_t result = sum_of_cubes_minus_sum(n);
    if (result == -1) {
        printf("Overflow detected\n");
        return 1;
    }
    printf("%" PRId64 "\n", result);
    return 0;
}