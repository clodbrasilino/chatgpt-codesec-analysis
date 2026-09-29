#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int max3(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

int lcsOfThree(const char* X, const char* Y, const char* Z, int m, int n, int o) {
    if (m < 0 || n < 0 || o < 0) return -1;
    
    size_t size = (size_t)(m + 1) * (n + 1) * (o + 1);
    if (size == 0 || size > SIZE_MAX / sizeof(int)) return -1;
    
    int *L = (int*)malloc(size * sizeof(int));
    if (!L) return -1;

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= o; k++) {
                int index = i * (n + 1) * (o + 1) + j * (o + 1) + k;
                if (i == 0 || j == 0 || k == 0) {
                    L[index] = 0;
                } else if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1]) {
                    int prev_idx = (i - 1) * (n + 1) * (o + 1) + (j - 1) * (o + 1) + (k - 1);
                    L[index] = L[prev_idx] + 1;
                } else {
                    int idx1 = (i - 1) * (n + 1) * (o + 1) + j * (o + 1) + k;
                    int idx2 = i * (n + 1) * (o + 1) + (j - 1) * (o + 1) + k;
                    int idx3 = i * (n + 1) * (o + 1) + j * (o + 1) + (k - 1);
                    L[index] = max3(L[idx1], L[idx2], L[idx3]);
                }
            }
        }
    }

    int result = L[m * (n + 1) * (o + 1) + n * (o + 1) + o];
    free(L);
    return result;
}

int main(void) {
    int m, n, o;

    while (scanf("%d %d %d", &m, &n, &o) == 3) {
        if (m <= 0 || n <= 0 || o <= 0) continue;
        
        if (m > 400 || n > 400 || o > 400) continue; 

        char *X = (char*)malloc((m + 1) * sizeof(char));
        char *Y = (char*)malloc((n + 1) * sizeof(char));
        char *Z = (char*)malloc((o + 1) * sizeof(char));

        if (!X || !Y || !Z) {
            free(X);
            free(Y);
            free(Z);
            continue;
        }

        char fmtX[32], fmtY[32], fmtZ[32];
        snprintf(fmtX, sizeof(fmtX), "%%%ds", m);
        snprintf(fmtY, sizeof(fmtY), "%%%ds", n);
        snprintf(fmtZ, sizeof(fmtZ), "%%%ds", o);

        if (scanf(fmtX, X) == 1 && scanf(fmtY, Y) == 1 && scanf(fmtZ, Z) == 1) {
            int lcs_length = lcsOfThree(X, Y, Z, m, n, o);
            if (lcs_length != -1) {
                printf("%d\n", lcs_length);
            }
        }

        free(X);
        free(Y);
        free(Z);
    }

    return 0;
}