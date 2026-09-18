#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_nth_term(long long first_term, long long common_diff, long long n)
{
    long long term_index = n - 1;
    long long result;

    if (common_diff > 0) {
        if (term_index > LLONG_MAX / common_diff) {
            fprintf(stderr, "Error: Arithmetic overflow detected.\n");
            exit(EXIT_FAILURE);
        }
    } else if (common_diff < 0) {
        if (term_index > LLONG_MIN / common_diff) {
            fprintf(stderr, "Error: Arithmetic overflow detected.\n");
            exit(EXIT_FAILURE);
        }
    }

    long long product = term_index * common_diff;

    if ((product > 0 && first_term > LLONG_MAX - product) ||
        (product < 0 && first_term < LLONG_MIN - product)) {
        fprintf(stderr, "Error: Arithmetic overflow detected.\n");
        exit(EXIT_FAILURE);
    }

    result = first_term + product;
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000009,time:5538,execs:2684,op:havoc,rep:1; likely memory-safety defect
  */

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