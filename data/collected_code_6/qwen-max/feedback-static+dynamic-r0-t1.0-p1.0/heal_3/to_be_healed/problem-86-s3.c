#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t nth_centered_hexagonal_number(int64_t n) {
    if (n > (INT64_MAX - 1) / 3 + 1 || n < 1) {
        fprintf(stderr, "Input value out of valid range for int64_t.\n");
        return -1;
    }
    int64_t temp = 3 * n;
    if (temp < 0) {
        fprintf(stderr, "Overflow detected.\n");
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 333333333333 * 111111111110 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:624,execs:287,op:havoc,rep:5)
     */
    int64_t result = temp * (n - 1) + 1;
    if (result < 0) {
        fprintf(stderr, "Overflow detected.\n");
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