#include <stdio.h>
#include <stdlib.h>

long long sum_of_arithmetic_progression(long long a, long long d, long long n) {
    if (n < 0) {
        return 0;
    }
    return (n * ((2 * a) + (n - 1) * d)) / 2;
}

int main(void) {
    long long a = 0;
    long long d = 0;
    long long n = 0;
    long long sum = 0;
    int result = 0;

    result = scanf("%lld %lld %lld", &a, &d, &n);
    if (result != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }

    sum = sum_of_arithmetic_progression(a, d, n);
    
    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}