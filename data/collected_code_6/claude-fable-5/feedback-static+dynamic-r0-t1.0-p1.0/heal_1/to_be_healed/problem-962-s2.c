#include <stdio.h>
#include <stdlib.h>

long long sum_even_in_range(long long l, long long r)
{
    long long first;
    long long last;
    long long count;

    if (l > r) {
        return 0;
    }

    first = (l % 2 == 0) ? l : l + 1;
    last = (r % 2 == 0) ? r : r - 1;

    if (first > last) {
        return 0;
    }

    count = ((last - first) / 2) + 1;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 200000000000001 * 244444444444444 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000005,time:3939,execs:2476,op:havoc,rep:10)
     * UBSan: signed integer overflow: 16666666665 * 16666666668 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:625,execs:407,op:havoc,rep:2)
     * UBSan: signed integer overflow: 4 + 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:1909,execs:1213,op:havoc,rep:2)
     * UBSan: signed integer overflow: 4611686018427387902 * -4611686018427387903 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:1909,execs:1213,op:havoc,rep:2)
     */
    return count * ((first + last) / 2);
}

int main(void)
{
    long long l;
    long long r;
    long long result;

    printf("Enter lower bound: ");
    if (scanf("%lld", &l) != 1) {
        fprintf(stderr, "Invalid input for lower bound\n");
        return EXIT_FAILURE;
    }

    printf("Enter upper bound: ");
    if (scanf("%lld", &r) != 1) {
        fprintf(stderr, "Invalid input for upper bound\n");
        return EXIT_FAILURE;
    }

    if (l < 1 || r < 1) {
        fprintf(stderr, "Bounds must be natural numbers (>= 1)\n");
        return EXIT_FAILURE;
    }

    if (l > r) {
        fprintf(stderr, "Lower bound must not exceed upper bound\n");
        return EXIT_FAILURE;
    }

    result = sum_even_in_range(l, r);
    printf("Sum of even numbers in [%lld, %lld] = %lld\n", l, r, result);

    return EXIT_SUCCESS;
}