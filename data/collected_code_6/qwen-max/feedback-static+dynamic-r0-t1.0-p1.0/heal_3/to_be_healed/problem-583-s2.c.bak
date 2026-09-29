#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (n < 0 || k < 0) return 0;
    if (k > n) return 0;
    if (k > n - k) k = n - k;
    unsigned long long res = 1;
    for (int i = 0; i < k; ++i) {
        if (res > ULLONG_MAX / (n - i)) return 0;
        res *= (n - i);
        if (res < (i + 1)) return 0;
        res /= (i + 1);
    }
    return res;
}

unsigned long long catalan_number(int n) {
    if (n <= 1) return 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 1410065407 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:628,execs:282,op:havoc,rep:6)
     */
    unsigned long long bc = binomial_coefficient(2 * n, n);
    if (bc == 0 || bc > ULLONG_MAX / (n + 1)) return 0;
    return bc / (n + 1);
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Input is not an integer.\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        printf("Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = catalan_number(n);
    if (result == 0) {
        printf("Result is out of range or input is invalid.\n");
        return EXIT_FAILURE;
    }
    printf("The %dth Catalan number is: %llu\n", n, result);

    return 0;
}