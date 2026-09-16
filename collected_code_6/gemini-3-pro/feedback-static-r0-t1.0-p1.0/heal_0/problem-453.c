#include <stdio.h>
#include <stdlib.h>

long long sum_of_even_factors(long long n)
{
    long long sum = 0;
    
    if (n <= 0) {
        return 0;
    }

    if (n % 2 != 0) {
        return 0;
    }

    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 == 0) {
                sum += i;
            }
            if (i * i != n) {
                long long factor = n / i;
                if (factor % 2 == 0) {
                    sum += factor;
                }
            }
        }
    }

    return sum;
}

int main(void)
{
    long long number = 0;
    
    if (scanf("%lld", &number) != 1) {
        return EXIT_FAILURE;
    }

    long long result = sum_of_even_factors(number);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}