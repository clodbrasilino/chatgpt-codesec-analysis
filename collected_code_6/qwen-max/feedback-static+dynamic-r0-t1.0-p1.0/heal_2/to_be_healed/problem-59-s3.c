#include <stdio.h>
#include <stdint.h>

int64_t nth_octagonal_number(int n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -5341009239 * -1780336413 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:2141,execs:977,op:havoc,rep:2)
     */
    return 3 * (int64_t)n * n - 2 * (int64_t)n;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    int64_t result = nth_octagonal_number(n);
    /* Possible weaknesses found:
     *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("The %dth octagonal number is: %lld\n", n, result);
    return 0;
}