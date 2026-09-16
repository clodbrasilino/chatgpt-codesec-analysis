#include <stdio.h>
#include <stdlib.h>

static long long sum_even_in_range(long long l, long long r)
{
    long long first;
    long long last;
    long long count;

    if (l > r) {
        return 0;
    }

    if (l < 2) {
        l = 2;
    }

    if (r < 2) {
        return 0;
    }

    first = (l % 2 == 0) ? l : l + 1;
    last = (r % 2 == 0) ? r : r - 1;

    if (first > last) {
        return 0;
    }

    count = ((last - first) / 2) + 1;

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

    result = sum_even_in_range(l, r);
    printf("Sum of even natural numbers in [%lld, %lld] = %lld\n", l, r, result);

    return EXIT_SUCCESS;
}