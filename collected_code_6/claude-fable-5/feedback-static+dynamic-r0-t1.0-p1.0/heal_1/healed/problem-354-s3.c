#include <stdio.h>
#include <stdlib.h>

int nth_term(long long a, long long d, long long n, long long *result)
{
    long long offset;
    long long product;

    if (__builtin_sub_overflow(n, 1LL, &offset)) {
        return -1;
    }

    if (__builtin_mul_overflow(offset, d, &product)) {
        return -1;
    }

    if (__builtin_add_overflow(a, product, result)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    long long a;
    long long d;
    long long n;
    long long result;

    printf("Enter the first term: ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input for first term\n");
        return EXIT_FAILURE;
    }

    printf("Enter the common difference: ");
    if (scanf("%lld", &d) != 1) {
        fprintf(stderr, "Invalid input for common difference\n");
        return EXIT_FAILURE;
    }

    printf("Enter the term number: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for term number\n");
        return EXIT_FAILURE;
    }

    if (n < 1) {
        fprintf(stderr, "Term number must be a positive integer\n");
        return EXIT_FAILURE;
    }

    if (nth_term(a, d, n, &result) != 0) {
        fprintf(stderr, "Arithmetic overflow detected while computing the term\n");
        return EXIT_FAILURE;
    }

    printf("The %lld-th term is: %lld\n", n, result);

    return EXIT_SUCCESS;
}