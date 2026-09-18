#include <stdio.h>
#include <stdlib.h>

long long sum_of_cubes(int n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 70835277958146529 * 266148978 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1237,execs:538,op:havoc,rep:2)
     * UBSan: signed integer overflow: 171467558298936900 * 555556 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:1468,execs:634,op:havoc,rep:9)
     * UBSan: signed integer overflow: -1629121199669919182 * 266148978 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1237,execs:538,op:havoc,rep:2)
     */
    return (long long)n * n * (n + 1) * (n + 1) / 4;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    long long result = sum_of_cubes(n);
    printf("The sum of the series 1^3 + 2^3 + ... + %d^3 is %lld\n", n, result);
    return EXIT_SUCCESS;
}