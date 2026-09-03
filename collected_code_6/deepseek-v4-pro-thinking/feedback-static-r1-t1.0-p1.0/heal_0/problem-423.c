#include <stdio.h>
#include <stdlib.h>

long long maxGold(int **mine, int n, int m) {
    if (mine == NULL || n <= 0 || m <= 0) {
        return -1;
    }
    long long *prev = malloc(n * sizeof(long long));
    long long *curr = malloc(n * sizeof(long long));
    if (prev == NULL || curr == NULL) {
        free(prev);
        free(curr);
        return -1;
    }
    for (int i = 0; i < n; i++) {
        prev[i] = mine[i][0];
    }
    for (int j = 1; j < m; j++) {
        for (int i = 0; i < n; i++) {
            long long best = prev[i];
            if (i > 0 && prev[i - 1] > best) {
                best = prev[i - 1];
            }
            if (i < n - 1 && prev[i + 1] > best) {
                best = prev[i + 1];
            }
            curr[i] = best + mine[i][j];
        }
        long long *temp = prev;
        prev = curr;
        curr = temp;
    }
    long long max = prev[0];
    for (int i = 1; i < n; i++) {
        if (prev[i] > max) {
            max = prev[i];
        }
    }
    free(prev);
    free(curr);
    return max;
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int **mine = malloc(n * sizeof(int *));
    if (mine == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++) {
        mine[i] = malloc(m * sizeof(int));
        if (mine[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int k = 0; k < i; k++) {
                free(mine[k]);
            }
            free(mine);
            return EXIT_FAILURE;
        }
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &mine[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                for (int k = 0; k <= i; k++) {
                    free(mine[k]);
                }
                free(mine);
                return EXIT_FAILURE;
            }
        }
    }
    long long result = maxGold(mine, n, m);
    if (result == -1) {
        fprintf(stderr, "Error computing maximum gold\n");
        for (int i = 0; i < n; i++) {
            free(mine[i]);
        }
        free(mine);
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    for (int i = 0; i < n; i++) {
        free(mine[i]);
    }
    free(mine);
    return EXIT_SUCCESS;
}