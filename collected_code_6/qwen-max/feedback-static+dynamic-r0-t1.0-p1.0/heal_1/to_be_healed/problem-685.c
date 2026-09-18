#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int sum_of_primes(int n) {
    int sum = 0;
    for (int i = 2; i <= n; ++i) {
        if (is_prime(i)) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2147431330 + 225287 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:2608,execs:1044,op:havoc,rep:4)
             */
            sum += i;
        }
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if (n < 2) {
        printf("No prime numbers in the given range.\n");
        return 0;
    }

    int sum = sum_of_primes(n);
    printf("Sum of primes up to %d: %d\n", n, sum);

    return 0;
}