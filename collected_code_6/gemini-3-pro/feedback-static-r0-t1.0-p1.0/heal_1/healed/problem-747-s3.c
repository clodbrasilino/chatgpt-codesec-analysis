#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX_STR_LEN 4096

int lcsOfThree(const char *X, const char *Y, const char *Z) {
    if (!X || !Y || !Z) {
        return 0;
    }

    int m = (int)strnlen(X, MAX_STR_LEN);
    int n = (int)strnlen(Y, MAX_STR_LEN);
    int o = (int)strnlen(Z, MAX_STR_LEN);

    int *L = (int *)malloc((m + 1) * (n + 1) * (o + 1) * sizeof(int));
    if (!L) {
        return -1;
    }

    #define IDX(i, j, k) (((i) * (n + 1) + (j)) * (o + 1) + (k))

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= o; k++) {
                if (i == 0 || j == 0 || k == 0) {
                    L[IDX(i, j, k)] = 0;
                } else if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1]) {
                    L[IDX(i, j, k)] = L[IDX(i - 1, j - 1, k - 1)] + 1;
                } else {
                    L[IDX(i, j, k)] = MAX(MAX(L[IDX(i - 1, j, k)], L[IDX(i, j - 1, k)]), L[IDX(i, j, k - 1)]);
                }
            }
        }
    }

    int result = L[IDX(m, n, o)];

    free(L);
    #undef IDX

    return result;
}

int main(void) {
    const char *X = "AGGT12";
    const char *Y = "12TXAYB";
    const char *Z = "12XBA";

    int result = lcsOfThree(X, Y, Z);

    if (result == -1) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Length of LCS is %d\n", result);

    return EXIT_SUCCESS;
}