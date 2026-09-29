#include <stdio.h>
#include <stdlib.h>

static long long sum_of_odds(long long l, long long r)
{
    long long first;
    long long last;
    long long count;

    if (l > r) {
        return 0;
    }

    if (l < 1) {
        l = 1;
    }

    if (l > r) {
        return 0;
    }

    first = (l % 2 == 0) ? (l + 1) : l;
    last = (r % 2 == 0) ? (r - 1) : r;

    if (first > last) {
        return 0;
    }

    count = ((last - first) / 2) + 1;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:18613,execs:11342,op:havoc,rep:7)
     * UBSan: signed integer overflow: 4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:18613,execs:11342,op:havoc,rep:7)
     * UBSan: signed integer overflow: 388888888888887 * 388888888888891 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000007,time:9163,execs:5531,op:havoc,rep:4)
     */
    return count * ((first + last) / 2);
}

int main(void)
{
    long long l;
    long long r;
    long long result;

    printf("Enter the lower bound: ");
    if (scanf("%lld", &l) != 1) {
        fprintf(stderr, "Error: invalid input for lower bound.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the upper bound: ");
    if (scanf("%lld", &r) != 1) {
        fprintf(stderr, "Error: invalid input for upper bound.\n");
        return EXIT_FAILURE;
    }

    if (l > r) {
        fprintf(stderr, "Error: lower bound must not exceed upper bound.\n");
        return EXIT_FAILURE;
    }

    result = sum_of_odds(l, r);

    printf("Sum of odd natural numbers in [%lld, %lld] is %lld\n", l, r, result);

    return EXIT_SUCCESS;
}