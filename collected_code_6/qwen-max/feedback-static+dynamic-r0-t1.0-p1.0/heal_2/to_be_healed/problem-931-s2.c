#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

bool is_safe_multiply(int64_t a, int64_t b) {
    if (a > 0 && b > 0 && a > (INT64_MAX / b)) {
        return false;
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'b<0' is not redundant
     *  Expression 'b' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
     *  Negative value is converted to an unsigned value
     */
    if (a < 0 && b < 0 && a < (INT64_MIN / b)) {
        return false;
    }
    if (a > 0 && b < 0 && b < (INT64_MIN / a)) {
        return false;
    }
    if (a < 0 && b > 0 && a < (INT64_MIN / b)) {
        return false;
    }
    return true;
}

int64_t sum_of_cubes(int n) {
    int64_t temp1 = (int64_t)n * n;
    if (!is_safe_multiply(n, n)) return 0;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6049381039506289 * 77777768 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:273,execs:128,op:havoc,rep:4)
     */
    int64_t temp2 = temp1 * (n + 1);
    if (!is_safe_multiply(temp1, n + 1)) return 0;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 470499478758162 * 77778 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:1030,execs:472,op:havoc,rep:4)
     */
    int64_t result = temp2 * (n + 1) / 4;
    if (!is_safe_multiply(temp2, n + 1)) return 0;

    return result;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    int64_t result = sum_of_cubes(n);
    if (result == 0) {
        fprintf(stderr, "Overflow detected. Please enter a smaller value for n.\n");
        return EXIT_FAILURE;
    }
    printf("The sum of the series 1^3 + 2^3 + ... + %d^3 is %" PRId64 "\n", n, result);
    return EXIT_SUCCESS;
}