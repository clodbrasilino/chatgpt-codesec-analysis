#include <stdio.h>

long long cube_sum_of_odds(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        int odd_number = 2 * i - 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9222615723651324400 + 796108265857241 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:487,execs:235,op:havoc,rep:7)
         */
        sum += (long long)odd_number * odd_number * odd_number;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = cube_sum_of_odds(n);
    printf("The cube sum of the first %d odd natural numbers is: %lld\n", n, result);
    return 0;
}