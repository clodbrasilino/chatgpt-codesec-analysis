#include <stdio.h>
#include <stdlib.h>

#define MAX_N 90

static unsigned long long count_tilings(int n)
{
    unsigned long long prev;
    unsigned long long curr;
    unsigned long long next;
    int i;

    if (n <= 0) {
        return 0ULL;
    }
    if (n == 1) {
        return 1ULL;
    }
    if (n == 2) {
        return 2ULL;
    }

    prev = 1ULL;
    curr = 2ULL;

    for (i = 3; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}

int main(void)
{
    int n;
    int result;
    unsigned long long ways;

    printf("Enter board length n (2 x n board, 1 to %d): ", MAX_N);

    result = scanf("%d", &n);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 1 || n > MAX_N) {
        fprintf(stderr, "Error: n must be between 1 and %d.\n", MAX_N);
        return EXIT_FAILURE;
    }

    ways = count_tilings(n);

    printf("Number of ways to tile a 2 x %d board: %llu\n", n, ways);

    return EXIT_SUCCESS;
}