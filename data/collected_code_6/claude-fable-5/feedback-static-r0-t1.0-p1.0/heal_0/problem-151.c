#include <stdio.h>
#include <stdlib.h>

static unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    while (b != 0ULL) {
        unsigned long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

static int is_coprime(unsigned long long a, unsigned long long b)
{
    if (a == 0ULL && b == 0ULL) {
        return 0;
    }
    return (gcd(a, b) == 1ULL) ? 1 : 0;
}

int main(void)
{
    unsigned long long num1 = 0ULL;
    unsigned long long num2 = 0ULL;
    int result = 0;

    printf("Enter the first positive integer: ");
    if (scanf("%llu", &num1) != 1) {
        fprintf(stderr, "Error: invalid input for the first number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the second positive integer: ");
    if (scanf("%llu", &num2) != 1) {
        fprintf(stderr, "Error: invalid input for the second number.\n");
        return EXIT_FAILURE;
    }

    result = is_coprime(num1, num2);

    if (result == 1) {
        printf("%llu and %llu are co-prime.\n", num1, num2);
    } else {
        printf("%llu and %llu are not co-prime.\n", num1, num2);
    }

    return EXIT_SUCCESS;
}