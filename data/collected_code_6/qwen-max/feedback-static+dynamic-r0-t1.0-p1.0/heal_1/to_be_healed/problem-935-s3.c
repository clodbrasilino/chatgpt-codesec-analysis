#include <stdio.h>

long long sum_of_squares(int n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 1249946282 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:892,execs:408,op:havoc,rep:2)
     * UBSan: signed integer overflow: 896308649439773582 * 1893471573 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:273,execs:138,op:havoc,rep:3)
     * UBSan: signed integer overflow: 1562365709135569806 * -1795074731 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:892,execs:408,op:havoc,rep:2)
     */
    return (long long)n * (n + 1) * (2 * n + 1) / 6;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_squares(n);
    printf("The sum of squares from 1 to %d is: %lld\n", n, result);
    return 0;
}