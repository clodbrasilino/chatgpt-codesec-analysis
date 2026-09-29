#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int64_t nth_centered_hexagonal(int64_t n) {
    /* Possible weaknesses found:
     *  Assuming that condition 'n<-0x1FFFFFFFFFFFFFFFLL' is not redundant
     *  Assuming that condition 'n>0x1FFFFFFFFFFFFFFFLL' is not redundant
     */
    if (n > 0x1FFFFFFFFFFFFFFFLL || n < -0x1FFFFFFFFFFFFFFFLL) {
        fprintf(stderr, "Input out of range\n");
        return -1;
    }
    /* Possible weaknesses found:
     *  Assignment 'max_n=(9223372036854775807/3)+1', assigned value is 3074457345618258603
     */
    int64_t max_n = (INT64_MAX / 3) + 1;
    /* Possible weaknesses found:
     *  Condition 'n>=max_n' is always false [knownConditionTrueFalse]
     *  Condition 'n<=-max_n' is always false
     *  Condition 'n>=max_n' is always false
     *  Condition 'n<=-max_n' is always false [knownConditionTrueFalse]
     */
    if (n >= max_n || n <= -max_n) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 66666666666666 * 22222222222221 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:502,execs:218,op:havoc,rep:3)
     */
    return 3 * n * (n - 1) + 1;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal(n);
    if (result == -1) {
        return 1;
    }
    printf("The %ldth centered hexagonal number is: %ld\n", n, result);
    return 0;
}