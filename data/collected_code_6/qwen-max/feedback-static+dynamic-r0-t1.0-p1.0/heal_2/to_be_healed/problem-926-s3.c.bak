#include <stdio.h>

long derangement(long n) {
    long a = 1, b = 0;
    for (long i = 0; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 20 * 939765362752547227 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:277,execs:138,op:havoc,rep:4)
         * UBSan: signed integer overflow: -5188895624805881368 + -5784077728986054255 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:277,execs:138,op:havoc,rep:4)
         */
        long temp = (i + 1) * (a + b);
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) return 1;
    if (n < 0) return 1;
    printf("The %ld-th derangement number is: %ld\n", n, derangement(n));
    return 0;
}