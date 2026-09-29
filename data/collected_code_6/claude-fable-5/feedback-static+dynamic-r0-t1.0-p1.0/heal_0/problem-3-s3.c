#include <stdio.h>
#include <stdbool.h>

bool is_not_prime(long long n);

bool is_not_prime(long long n)
{
    if (n < 2) {
        return true;
    }
    if (n < 4) {
        return false;
    }
    if (n % 2 == 0) {
        return true;
    }
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return true;
        }
    }
    return false;
}

int main(void)
{
    long long number = 0;

    printf("Enter an integer: ");
    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (is_not_prime(number)) {
        printf("%lld is not a prime number.\n", number);
    } else {
        printf("%lld is a prime number.\n", number);
    }

    return 0;
}