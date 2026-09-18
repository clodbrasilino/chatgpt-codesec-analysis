#include <stdio.h>

long centered_hexagonal_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:255,execs:134,op:havoc,rep:2)
     * UBSan: signed integer overflow: 66666666666666 * 22222222222221 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000002,time:454,execs:219,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775805 * 9223372036854775806 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:255,execs:134,op:havoc,rep:2)
     */
    return 3 * n * (n - 1) + 1;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        return 1;
    }
    long result = centered_hexagonal_number(n);
    printf("The %ldth centered hexagonal number is: %ld\n", n, result);
    return 0;
}