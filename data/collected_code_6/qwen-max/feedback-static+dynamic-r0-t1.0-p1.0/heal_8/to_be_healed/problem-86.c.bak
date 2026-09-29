#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int64_t centered_hexagonal_number(int64_t n) {
    if (n <= 0 || n > INT64_MAX / 3) {
        return -1;
    }
    int64_t intermediate_result = 3 * n - 3;
    if (intermediate_result > INT64_MAX - n) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6666666666663 * 2222222222222 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:648,execs:305,op:havoc,rep:8)
     */
    int64_t result = intermediate_result * n + 1;
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    int64_t result = centered_hexagonal_number(n);
    if (result == -1) {
        printf("Invalid input. The number is too large.\n");
    } else {
        printf("The %" PRId64 "th centered hexagonal number is: %" PRId64 "\n", n, result);
    }
    return 0;
}