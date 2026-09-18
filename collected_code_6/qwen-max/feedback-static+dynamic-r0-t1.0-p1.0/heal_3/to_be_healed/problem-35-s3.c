#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t nth_rectangular_number(int64_t n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:2985,execs:1436,op:havoc,rep:8)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:2985,execs:1436,op:havoc,rep:8)
     * UBSan: signed integer overflow: 900000007100000 * 900000007100001 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000004,time:4485,execs:2174,op:havoc,rep:4)
     */
    int64_t result = n * (n + 1);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:2985,execs:1436,op:havoc,rep:8)
     */
    if (result / n != n + 1) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }
    int64_t result = nth_rectangular_number(n);
    if (result == -1) {
        return 1;
    }
    printf("The %" PRId64 "-th rectangular number is: %" PRId64 "\n", n, result);
    return 0;
}