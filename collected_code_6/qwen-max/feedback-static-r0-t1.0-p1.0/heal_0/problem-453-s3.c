#include <stdio.h>
#include <stdlib.h>

long sum_of_even_factors(long n) {
    long sum = 0;
    if (n % 2 != 0) return 0;
    for (long i = 2; i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    long result = sum_of_even_factors(number);
    printf("Sum of even factors is: %ld\n", result);
    return 0;
}