#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t nth_rectangular_number(int64_t n) {
    if (n > 0 && n < INT64_MAX / 2) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4444444444 * 4444444445 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:588,execs:277,op:havoc,rep:4)
         */
        int64_t result = n * (n + 1);
        if (result / n == n + 1) {
            return result;
        }
    }
    fprintf(stderr, "Overflow detected\n");
    return -1;
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