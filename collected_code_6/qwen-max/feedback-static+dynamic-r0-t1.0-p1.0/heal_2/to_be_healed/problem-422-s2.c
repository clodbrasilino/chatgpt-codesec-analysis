#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

double average_of_cubes(int n) {
    if (n <= 0) return 0.0;

    int64_t sum = 0;
    for (int i = 1; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223193340756366400 + 473384830201856 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:117,execs:140,op:havoc,rep:4)
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:117,execs:140,op:havoc,rep:4)
         */
        sum += (int64_t)i * i * i;
    }
    return (double)sum / n;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    double result = average_of_cubes(n);
    printf("The average of cubes of first %d natural numbers is: %.2f\n", n, result);

    return EXIT_SUCCESS;
}