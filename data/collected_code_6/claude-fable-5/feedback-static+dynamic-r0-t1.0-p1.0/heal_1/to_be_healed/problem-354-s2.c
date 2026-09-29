#include <stdio.h>
#include <stdlib.h>

long long nth_term(long long a, long long d, long long n)
{
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 215 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:17235,execs:10584,op:havoc,rep:60)
     * UBSan: signed integer overflow: 11111111 + 9223372036854775798 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:11232,execs:6887,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775806 * 5 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:11232,execs:6887,op:havoc,rep:2)
     */
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