#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX_LEN 4096

int lcsOfThree(const char *X, const char *Y, const char *Z) {
    if (!X || !Y || !Z) {
        return 0;
    }

    size_t m = strnlen(X, MAX_LEN);
    size_t n = strnlen(Y, MAX_LEN);
    size_t o = strnlen(Z, MAX_LEN);

    int *L = (int *)malloc((m + 1) * (n + 1) * (o + 1) * sizeof(int));
    if (!L) {
        return -1;
    }

    #define L_IDX(i, j, k) L[(i) * (n + 1) * (o + 1) + (j) * (o + 1) + (k)]

    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            for (size_t k = 0; k <= o; k++) {
                if (i == 0 || j == 0 || k == 0) {
                    L_IDX(i, j, k) = 0;
                } else if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1]) {
                    L_IDX(i, j, k) = L_IDX(i - 1, j - 1, k - 1) + 1;
                } else {
                    L_IDX(i, j, k) = MAX(MAX(L_IDX(i - 1, j, k), L_IDX(i, j - 1, k)), L_IDX(i, j, k - 1));
                }
            }
        }
    }

    int result = L_IDX(m, n, o);
    
    free(L);
    #undef L_IDX

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