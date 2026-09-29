#include <stdio.h>

long long cube_sum_natural(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:603,execs:300,op:havoc,rep:13)
         */
        long long cube = (long long)i * i * i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223193340756366400 + 473384830201856 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:603,execs:300,op:havoc,rep:13)
         */
        sum += cube;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("Cube sum of first %d natural numbers: %lld\n", n, cube_sum_natural(n));
    return 0;
}