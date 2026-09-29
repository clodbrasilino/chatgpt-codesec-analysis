#include <stdio.h>
#include <stdlib.h>

long long find_difference(int n) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }
    long long sum = (long long)n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 642947437362191676 * 642947437362191676 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:631,execs:434,op:quick,pos:2)
     */
    long long sum_cubes = sum * sum;
    return sum_cubes - sum;
}

int main(void) {
    int n = 0;
    if (scanf("%d", &n) != 1) {
        exit(EXIT_FAILURE);
    }
    long long result = find_difference(n);
    printf("%lld\n", result);
    return 0;
}