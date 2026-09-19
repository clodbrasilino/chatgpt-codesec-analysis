#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_nth_term(long long first_term, long long common_diff, long long n)
{
    if (n <= 0) {
        fprintf(stderr, "Error: Invalid term number.\n");
        exit(EXIT_FAILURE);
    }

    if (n == 1) {
        return first_term;
    }

    long long k = n - 1;

    if (common_diff > 0) {
        if (first_term > 0) {
            if (k > (LLONG_MAX - first_term) / common_diff) {
                fprintf(stderr, "Error: Arithmetic overflow detected.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            if ((unsigned long long)k > ((unsigned long long)LLONG_MAX - (unsigned long long)first_term) / (unsigned long long)common_diff) {
                fprintf(stderr, "Error: Arithmetic overflow detected.\n");
                exit(EXIT_FAILURE);
            }
        }
    } else if (common_diff < 0) {
        if (common_diff == LLONG_MIN) {
            if (k > 1) {
                fprintf(stderr, "Error: Arithmetic overflow detected.\n");
                exit(EXIT_FAILURE);
            }
            if (first_term < 0) {
                fprintf(stderr, "Error: Arithmetic overflow detected.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            if (first_term < 0) {
                if ((unsigned long long)k > ((unsigned long long)first_term - (unsigned long long)LLONG_MIN) / (unsigned long long)(-common_diff)) {
                    fprintf(stderr, "Error: Arithmetic overflow detected.\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                if ((unsigned long long)k > ((unsigned long long)LLONG_MAX - (unsigned long long)first_term) / (unsigned long long)(-common_diff)) {
                    fprintf(stderr, "Error: Arithmetic overflow detected.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    return first_term + k * common_diff;
}

int main(void)
{
    long long first_term, common_diff, n;

    printf("Enter the first term: ");
    if (scanf("%lld", &first_term) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the common difference: ");
    if (scanf("%lld", &common_diff) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the term number (n): ");
    if (scanf("%lld", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    printf("The %lld-th term is: %lld\n", n, find_nth_term(first_term, common_diff, n));

    return EXIT_SUCCESS;
}