#include <stdio.h>
#include <stdlib.h>

long long binomial_coefficient(int n, int k) {
    long long res = 1;
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 109520053442532348 * 6661 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:1252,execs:524,op:havoc,rep:3)
         */
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

long long sum_even_index_binomial_coefficients(int n) {
    long long sum = 0;
    for (int i = 0; i <= n; i += 2)
        sum += binomial_coefficient(n, i);
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    long long result = sum_even_index_binomial_coefficients(n);
    printf("Sum of even index binomial coefficients: %lld\n", result);
    return EXIT_SUCCESS;
}