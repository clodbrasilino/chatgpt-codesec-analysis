#include <stdio.h>
#include <stdlib.h>

static int *memo = NULL;
static int memo_size = 0;

static int max3(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

static int compute_max_sum(int n) {
    if (n < memo_size && memo[n] != -1) {
        return memo[n];
    }

    int result;
    if (n <= 1) {
        result = n;
    } else {
        int part1 = n / 2;
        int part2 = n / 3;
        int part3 = n / 4;
        result = max3(n, compute_max_sum(part1) + compute_max_sum(part2) + compute_max_sum(part3));
    }

    if (n < memo_size) {
        memo[n] = result;
    }
    return result;
}

int max_sum_by_division(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 0;
    }

    memo_size = n + 1;
    memo = (int *)malloc((size_t)memo_size * sizeof(int));
    if (memo == NULL) {
        return 0;
    }

    for (int i = 0; i < memo_size; i++) {
        memo[i] = -1;
    }

    int result = compute_max_sum(n);
    free(memo);
    memo = NULL;
    memo_size = 0;
    return result;
}

int main(void) {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int result = max_sum_by_division(n);
    printf("Maximum sum: %d\n", result);

    return 0;
}