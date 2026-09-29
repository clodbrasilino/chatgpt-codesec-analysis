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
     *  Assignment 'max_n=9223372036854775807/3', assigned value is 3074457345618258602
     */
    int64_t max_n = (INT64_MAX / 3);
    /* Possible weaknesses found:
     *  Condition 'n<-max_n' is always false [knownConditionTrueFalse]
     *  Condition 'n<-max_n' is always false
     *  Condition 'n>max_n' is always false [knownConditionTrueFalse]
     *  Condition 'n>max_n' is always false
     */
    if (n > max_n || n < -max_n) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1666666666666665 * 555555555555554 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:159,execs:93,op:havoc,rep:2)
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
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal(n);
    if (result == -1) {
        return 1;
    }
    /* Possible weaknesses found:
     *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("The %lldth centered hexagonal number is: %lld\n", n, result);
    return 0;
}