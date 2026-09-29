#include <stdio.h>
#include <stdlib.h>

long long find_nth_term(long long first_term, long long common_diff, long long n)
{
    return first_term + (n - 1) * common_diff;
}

int main(void)
{
    long long first_term, common_diff, n;

    printf("Enter the first term: ");
    if (scanf("%lld", &first_term) != 1)
    {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the common difference: ");
    if (scanf("%lld", &common_diff) != 1)
    {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the term number (n): ");
    if (scanf("%lld", &n) != 1 || n <= 0)
    {
        fprintf(stderr, "Invalid input. n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    printf("The %lld-th term is: %lld\n", n, find_nth_term(first_term, common_diff, n));

    return EXIT_SUCCESS;
}