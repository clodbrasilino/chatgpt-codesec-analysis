#include <stdio.h>
#include <math.h>

int largestPrimeFactor(int n) {
    int maxPrime = -1;

    while (n % 2 == 0) {
        maxPrime = 2;
        n >>= 1;
    }

    while (n % 3 == 0) {
        maxPrime = 3;
        n = n/3;
    }

    for (int i = 5; i <= sqrt(n); i += 6) {
        while (n % i == 0) {
            maxPrime = i;
            n = n / i;
        }
        while (n % (i + 2) == 0) {
            maxPrime = i + 2;
            n = n / (i + 2);
        }
    }

    if (n > 4)
        maxPrime = n;

    return maxPrime;
}

int main() {
    int n = 15;
    printf("%d", largestPrimeFactor(n));
    return 0;
}