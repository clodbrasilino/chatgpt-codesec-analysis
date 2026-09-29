#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t nth_decagonal_number(int64_t n) {
    if (n > 0 && n <= 2305843009213693951LL) {
        int64_t max_val = LLONG_MAX / 4;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9999999999 * 9999999999 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000004,time:604,execs:243,op:quick,pos:10)
         */
        if (n > max_val || n * n > max_val) {
            return 0;
        }
        int64_t result = 4 * n * n - 3 * n;
        return result;
    }
    return 0;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int64_t result = nth_decagonal_number(n);
    if (result == 0) {
        fprintf(stderr, "Input too large for computation\n");
        return 1;
    }
    printf("The %" PRId64 "th decagonal number is: %" PRId64 "\n", n, result);
    return 0;
}