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
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -55 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000010,time:4349,execs:4329,op:havoc,rep:4)
         */
        if (k > (LLONG_MAX - first_term) / common_diff) {
            fprintf(stderr, "Error: Arithmetic overflow detected.\n");
            exit(EXIT_FAILURE);
        }
    } else if (common_diff < 0) {
        if (common_diff == LLONG_MIN) {
            if (k > 1 || (unsigned long long)first_term > (unsigned long long)LLONG_MAX + 1ULL) {
                fprintf(stderr, "Error: Arithmetic overflow detected.\n");
                exit(EXIT_FAILURE);
            }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1 - -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:4128,execs:4124,op:havoc,rep:3)
         */
        } else if (k > (first_term - LLONG_MIN) / (-common_diff)) {
            fprintf(stderr, "Error: Arithmetic overflow detected.\n");
            exit(EXIT_FAILURE);
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