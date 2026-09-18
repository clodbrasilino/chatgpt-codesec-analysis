#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_nth_term(long long first_term, long long common_diff, long long n)
{
    if (n <= 0) {
        fprintf(stderr, "Error: Invalid term number.\n");
        exit(EXIT_FAILURE);
    }

    if (common_diff > 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -5 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000006,time:12567,execs:5022,op:havoc,rep:1)
         */
        if (n - 1 > (LLONG_MAX - first_term) / common_diff) {
            fprintf(stderr, "Error: Arithmetic overflow detected.\n");
            exit(EXIT_FAILURE);
        }
    } else if (common_diff < 0) {
        if (first_term > 0) {
            if (n - 1 > (LLONG_MIN - first_term) / common_diff) {
                fprintf(stderr, "Error: Arithmetic overflow detected.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            if (n - 1 > (first_term - LLONG_MIN) / (-common_diff)) {
                fprintf(stderr, "Error: Arithmetic overflow detected.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return first_term + (n - 1) * common_diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000005,time:3841,execs:1636,op:havoc,rep:5; likely memory-safety defect
  */

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