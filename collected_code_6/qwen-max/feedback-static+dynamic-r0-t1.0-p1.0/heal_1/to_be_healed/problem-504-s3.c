#include <stdio.h>
#include <stdlib.h>

long long cube_sum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:423,execs:186,op:havoc,rep:3)
         * UBSan: signed integer overflow: 9223193340756366400 + 473384830201856 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:423,execs:186,op:havoc,rep:3)
         */
        sum += (long long)i * i * i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    long long result = cube_sum(n);
    printf("Cube sum of first %d natural numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}