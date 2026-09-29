#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_non_prime(long long n);

bool is_non_prime(long long n)
{
    if (n < 2LL) {
        return true;
    }
    if (n == 2LL || n == 3LL) {
        return false;
    }
    if ((n % 2LL) == 0LL || (n % 3LL) == 0LL) {
        return true;
    }
    for (long long i = 5LL; i <= n / i; i += 6LL) {
        if ((n % i) == 0LL || (n % (i + 2LL)) == 0LL) {
            return true;
        }
    }
    return false;
}

int main(void)
{
    long long value = 0LL;
    int result = 0;

    printf("Enter an integer: ");
    result = scanf("%lld", &value);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_non_prime(value)) {
        printf("%lld is not a prime number.\n", value);
    } else {
        printf("%lld is a prime number.\n", value);
    }

    return EXIT_SUCCESS;
}