#include <stdio.h>

long long sum_of_cubes(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:240,execs:126,op:havoc,rep:2)
     * UBSan: signed integer overflow: -3368135710256594135 * -3368135710256594135 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:356,execs:180,op:havoc,rep:3)
     * UBSan: signed integer overflow: 777777777777777777 * 777777777777777778 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:356,execs:180,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:240,execs:126,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:240,execs:126,op:havoc,rep:2)
     * UBSan: signed integer overflow: 302469135586419753 * 302469135586419753 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:378,execs:188,op:havoc,rep:5)
     */
    return (n * (n + 1) / 2) * (n * (n + 1) / 2);
}

int main() {
    long long n;
    printf("Enter a positive integer: ");
    if (scanf("%lld", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_cubes(n);
    printf("The sum of the cubes of the first %lld natural numbers is: %lld\n", n, result);
    return 0;
}