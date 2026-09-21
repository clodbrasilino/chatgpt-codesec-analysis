#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int64_t nth_centered_hexagonal(int64_t n) {
    if (n > 0x1FFFFFFFFFFFFFFFLL || n < -0x1FFFFFFFFFFFFFFFLL) {
        fprintf(stderr, "Input out of range\n");
        return -1;
    }
    int64_t max_n = LLONG_MAX / 3;
    if (n > max_n || n < -max_n) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 13333333332 * 4444444443 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000004,time:819,execs:347,op:quick,pos:10)
     */
    int64_t result = 3 * n * (n - 1) + 1;
    if (result < 0) {
        fprintf(stderr, "Result overflow\n");
        return -1;
    }
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &n) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal(n);
    if (result == -1) {
        return 1;
    }
    printf("The %" PRId64 "th centered hexagonal number is: %" PRId64 "\n", n, result);
    return 0;
}