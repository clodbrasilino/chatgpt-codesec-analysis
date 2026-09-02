#include <stdio.h>
#include <stdlib.h>

long long perrin(long n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;

    long long a = 3, b = 0, c = 2;
    for (long i = 3; i <= n; i++) {
        long long d = a + b;
        a = b;
        b = c;
        c = d;
    }
    return c;
}

long long sum_of_perrin(long n) {
    long long sum = 0;
    for (long i = 0; i <= n; i++) {
        sum += perrin(i);
    }
    return sum;
}

int main() {
    long n;
    if (scanf("%ld", &n) != 1) {
        return EXIT_FAILURE;
    }

    long long result = sum_of_perrin(n);
    printf("The sum of the first %ld Perrin numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}