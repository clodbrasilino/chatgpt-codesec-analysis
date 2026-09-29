#include <stdio.h>
#include <stdlib.h>

int find_max_sum(int n, int *memo) {
    if (n == 0) {
        return 0;
    }
    if (memo[n] != -1) {
        return memo[n];
    }
    int max_sum = n;
    for (int i = 1; i <= 3; i++) {
        int part = n / (4 - i);
        if (part > 0) {
            int rem = n - part;
            int current_sum = part + find_max_sum(rem, memo);
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    memo[n] = max_sum;
    return max_sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 1000000) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int *memo = (int *)malloc((n + 1) * sizeof(int));
    if (memo == NULL) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    int result = find_max_sum(n, memo);
    printf("%d\n", result);
    free(memo);
    return EXIT_SUCCESS;
}