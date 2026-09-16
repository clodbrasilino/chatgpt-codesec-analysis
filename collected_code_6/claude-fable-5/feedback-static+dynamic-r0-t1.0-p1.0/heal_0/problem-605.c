#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static bool is_prime(int n)
{
    if (n < 2) {
        return false;
    }
    if (n < 4) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    for (int i = 3; i <= n / i; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    int number = 0;

    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_prime(number)) {
        printf("%d is a prime number.\n", number);
    } else {
        printf("%d is not a prime number.\n", number);
    }

    return EXIT_SUCCESS;
}