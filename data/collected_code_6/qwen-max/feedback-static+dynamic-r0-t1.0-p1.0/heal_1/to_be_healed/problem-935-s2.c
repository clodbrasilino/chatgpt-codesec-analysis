#include <stdio.h>

long long sum_of_squares(int n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 1848304526 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:14985,execs:6757,op:havoc,rep:56)
     * UBSan: signed integer overflow: 444444444222222222 * 1333333333 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:255,execs:143,op:havoc,rep:5)
     * UBSan: signed integer overflow: 3416229622680389202 * -598358243 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:14985,execs:6757,op:havoc,rep:56)
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
    printf("Sum of squares up to %d is: %lld\n", n, result);
    return 0;
}