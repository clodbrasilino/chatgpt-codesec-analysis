#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool is_valid_input(int n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4938226172944 * 2222212 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:249,execs:133,op:havoc,rep:7)
     */
    return n > 0 && (long long)n * (long long)n * (long long)n <= LLONG_MAX;
}

long long cube_sum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long temp = (long long)i * (long long)i * (long long)i;
        if (sum > LLONG_MAX - temp) {
            fprintf(stderr, "Input too large, causing overflow.\n");
            exit(EXIT_FAILURE);
        }
        sum += temp;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || !is_valid_input(n)) {
        fprintf(stderr, "Invalid input. Please enter a smaller positive integer.\n");
        return EXIT_FAILURE;
    }

    long long result = cube_sum(n);
    printf("Cube sum of first %d natural numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}