#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_of_fourth_powers(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        long long i4 = (long long)i * i * i * i;
        if (sum > LLONG_MAX - i4) {
            fprintf(stderr, "Error: Sum overflow\n");
            exit(EXIT_FAILURE);
        }
        sum += i4;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    long long result = sum_of_fourth_powers(n);
    printf("The sum of the fourth powers of the first %d natural numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}