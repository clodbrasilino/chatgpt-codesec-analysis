#include <stdio.h>

long long cube_sum_of_evens(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int even = 2 * i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223013771341927200 + 796134035438568 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:433,execs:193,op:havoc,rep:5)
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:433,execs:193,op:havoc,rep:5)
         */
        sum += (long long)even * even * even;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return 1;
    }
    if (n <= 0) {
        fprintf(stderr, "Please enter a positive integer.\n");
        return 1;
    }
    long long result = cube_sum_of_evens(n);
    printf("The cube sum of first %d even natural numbers is: %lld\n", n, result);
    return 0;
}