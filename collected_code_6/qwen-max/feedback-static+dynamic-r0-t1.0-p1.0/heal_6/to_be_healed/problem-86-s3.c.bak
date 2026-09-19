#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t nth_centered_hexagonal_number(int64_t n) {
    if (n > (INT64_MAX - 1) / 3 + 1 || n < 1) {
        fprintf(stderr, "Input value out of valid range for int64_t.\n");
        return -1;
    }
    if (n == 1) {
        return 1;
    }
    int64_t temp = 3 * n;
    if (temp / 3 != n) {
        fprintf(stderr, "Overflow detected.\n");
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 29999999999766 * 9999999999921 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:500,execs:237,op:havoc,rep:4)
     */
    int64_t result = temp * (n - 1) + 1;
    if (result < 0 || (result - 1) / (n - 1) != 3 * n) {
        fprintf(stderr, "Overflow detected.\n");
        return -1;
    }
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1 || n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal_number(n);
    if (result == -1) {
        return 1;
    }
    printf("The %" PRIu64 "th centered hexagonal number is: %" PRIu64 "\n", n, result);
    return 0;
}