#include <stdio.h>

long long sum_of_fourth_powers(long n) {
    long long sum = 0;
    for (long i = 1; i <= n; ++i) {
        sum += (i * i * i * i);
    }
    return sum;
}

int main() {
    long n;
    printf("Enter a positive integer: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_fourth_powers(n);
    printf("The sum of the fourth powers of the first %ld natural numbers is: %lld\n", n, result);
    return 0;
}