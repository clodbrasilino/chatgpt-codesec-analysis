#include <stdio.h>
#include <stdlib.h>

long long difference_cubes_sum(long long n)
{
    long long sum_n = (n * (n + 1)) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 55555611111 * 55555611111 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:553,execs:343,op:quick,pos:6)
     */
    long long sum_cubes = sum_n * sum_n;
    return sum_cubes - sum_n;
}

int main(void)
{
    long long n = 0;

    printf("Enter a natural number n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 1) {
        fprintf(stderr, "Error: n must be a natural number (n >= 1).\n");
        return EXIT_FAILURE;
    }

    if (n > 3000000LL) {
        fprintf(stderr, "Error: n is too large and would cause overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Difference: %lld\n", difference_cubes_sum(n));

    return EXIT_SUCCESS;
}