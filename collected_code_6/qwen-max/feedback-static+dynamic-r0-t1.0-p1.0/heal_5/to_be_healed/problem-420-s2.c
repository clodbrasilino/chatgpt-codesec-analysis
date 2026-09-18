#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long cube_sum_of_even(int n) {
    if (n < 0 || n > INT_MAX / 2) {
        return -1;
    }
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223013771341927200 + 796134035438568 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:445,execs:211,op:havoc,rep:2)
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:445,execs:211,op:havoc,rep:2)
         */
        sum += (2 * (long long)i) * (2 * (long long)i) * (2 * (long long)i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of first even natural numbers: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    long long result = cube_sum_of_even(n);
    if (result == -1) {
        fprintf(stderr, "Input out of range. Please enter a smaller non-negative integer.\n");
        return EXIT_FAILURE;
    }
    printf("The cube sum of the first %d even natural numbers is: %lld\n", n, result);
    return EXIT_SUCCESS;
}