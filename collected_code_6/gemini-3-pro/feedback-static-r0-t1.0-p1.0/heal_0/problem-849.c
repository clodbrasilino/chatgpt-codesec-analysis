#include <stdio.h>
#include <stdlib.h>

long long sumOfPrimeDivisors(long long int n) {
    long long sum = 0;
    
    if (n <= 1) {
        return 0;
    }

    if (n % 2 == 0) {
        sum += 2;
        while (n % 2 == 0) {
            n /= 2;
        }
    }

    for (long long int i = 3; i * i <= n; i += 2) {
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

int main() {
    long long int n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    long long sum = sumOfPrimeDivisors(n);
    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}