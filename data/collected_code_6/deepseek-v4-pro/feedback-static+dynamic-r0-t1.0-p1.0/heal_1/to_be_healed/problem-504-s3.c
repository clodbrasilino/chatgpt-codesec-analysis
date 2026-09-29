#include <stdio.h>

long long cube_sum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:761,execs:377,op:havoc,rep:8)
         */
        long long cube = (long long)i * i * i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223193340756366400 + 473384830201856 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:761,execs:377,op:havoc,rep:8)
         */
        sum += cube;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter a natural number: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    printf("Cube sum = %lld\n", cube_sum(n));
    return 0;
}