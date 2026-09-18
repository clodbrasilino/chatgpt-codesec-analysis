#include <stdio.h>

long long sum_of_cubes_minus_sum(int n) {
    if (n < 1) {
        return 0;
    }
    long long sum = (long long)n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9876543456790 * 9876543456790 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:243,execs:135,op:havoc,rep:9)
     */
    long long sum_cubes = sum * sum;
    return sum_cubes - sum;
}

int main(void) {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("%lld\n", sum_of_cubes_minus_sum(n));
    return 0;
}