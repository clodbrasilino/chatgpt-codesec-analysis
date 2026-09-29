#include <stdio.h>
#include <stdlib.h>

long sum_of_even_factors(long n) {
    long sum = 0;
    if (n % 2 != 0) return 0;
    for (long i = 2; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                sum += n / i;
            }
        }
    }
    while (n % 2 == 0) n /= 2;
    for (long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            n /= i;
        }
    }
    if (n > 1 && n % 2 == 0) sum += n;
    else if (n > 1 && n % 2 != 0) sum += 2;
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