#include <stdio.h>
#include <math.h>

long long next_perfect_square(long long n) {
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:37490,execs:12930,op:havoc,rep:8)
     */
    long long root = sqrt(n);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:37490,execs:12930,op:havoc,rep:8)
     */
    if (root * root == n) {
        return (root + 1) * (root + 1);
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3037000500 * 3037000500 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:301,execs:127,op:havoc,rep:1)
         * UBSan: signed integer overflow: -9223372036854775807 * -9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:37490,execs:12930,op:havoc,rep:8)
         */
        return (root + 1) * (root + 1);
    }
}

int main() {
    long long number;
    printf("Enter a number: ");
    scanf("%lld", &number);
    long long result = next_perfect_square(number);
    printf("The next perfect square is: %lld\n", result);
    return 0;
}