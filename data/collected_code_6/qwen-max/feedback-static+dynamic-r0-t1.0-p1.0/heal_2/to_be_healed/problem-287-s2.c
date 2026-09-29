#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares(int n) {
    if (n < 1) {
        return -1;
    }
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223364155031292776 + 14522028965284 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:715,execs:313,op:havoc,rep:6)
         */
        sum += (long long)(2 * i) * (2 * i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }
    if (n < 1) {
        fprintf(stderr, "n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    long long result = sum_of_squares(n);
    if (result == -1) {
        fprintf(stderr, "Error in calculation.\n");
        return EXIT_FAILURE;
    }
    printf("Sum of squares of first %d even natural numbers is: %lld\n", n, result);
    return EXIT_SUCCESS;
}