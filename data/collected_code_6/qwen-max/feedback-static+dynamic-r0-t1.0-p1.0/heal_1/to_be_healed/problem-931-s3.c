#include <stdio.h>

long long sum_of_cubes(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223193340756366400 + 473384830201856 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:69,execs:45,op:havoc,rep:16)
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:69,execs:45,op:havoc,rep:16)
         */
        sum += (long long)i * i * i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_cubes(n);
    printf("The sum of cubes up to %d is: %lld\n", n, result);
    return 0;
}