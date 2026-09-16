#include <stdio.h>
#include <stdlib.h>

long long sum_of_prime_divisors(int n) {
    if (n <= 1) {
        return 0;
    }

    long long sum = 0;

    if (n % 2 == 0) {
        sum += 2;
        while (n % 2 == 0) {
            n /= 2;
        }
    }

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }

    if (n > 2) {
        sum += n;
    }

    return sum;
}

int main(void) {
    int num;
    
    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (num < 0) {
        return EXIT_FAILURE;
    }

    long long result = sum_of_prime_divisors(num);
    
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}