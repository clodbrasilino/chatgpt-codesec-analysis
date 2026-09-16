#include <stdio.h>
#include <stdlib.h>

long long nth_term(long long a, long long d, long long n)
{
    return a + (n - 1LL) * d;
}

int main(void)
{
    long long a;
    long long d;
    long long n;

    printf("Enter first term: ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input for first term\n");
        return EXIT_FAILURE;
    }

    printf("Enter common difference: ");
    if (scanf("%lld", &d) != 1) {
        fprintf(stderr, "Invalid input for common difference\n");
        return EXIT_FAILURE;
    }

    printf("Enter term number: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for term number\n");
        return EXIT_FAILURE;
    }

    if (n < 1) {
        fprintf(stderr, "Term number must be a positive integer\n");
        return EXIT_FAILURE;
    }

    printf("Term %lld of the arithmetic progression is: %lld\n", n, nth_term(a, d, n));

    return EXIT_SUCCESS;
}