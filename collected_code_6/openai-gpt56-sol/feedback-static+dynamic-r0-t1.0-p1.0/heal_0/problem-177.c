#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int find_pair(long long left, long long right, long long *first, long long *second)
{
    if (first == NULL || second == NULL || left <= 0 || right < left) {
        return 0;
    }

    if (left <= LLONG_MAX / 2) {
        long long candidate = left * 2;

        if (candidate <= right) {
            *first = left;
            *second = candidate;
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    long long left;
    long long right;
    long long first;
    long long second;

    if (scanf("%lld %lld", &left, &right) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (find_pair(left, right, &first, &second)) {
        printf("%lld %lld\n", first, second);
    } else {
        printf("-1 -1\n");
    }

    return EXIT_SUCCESS;
}