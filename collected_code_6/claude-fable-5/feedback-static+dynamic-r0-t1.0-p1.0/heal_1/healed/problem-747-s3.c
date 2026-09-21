#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096U

static int max3(int a, int b, int c)
{
    int m = a;
    if (b > m) {
        m = b;
    }
    if (c > m) {
        m = c;
    }
    return m;
}

static int lcs_of_three(const char *x, const char *y, const char *z)
{
    size_t lx;
    size_t ly;
    size_t lz;
    size_t i;
    size_t j;
    size_t k;
    int ***dp;
    int result;

    if ((x == NULL) || (y == NULL) || (z == NULL)) {
        return -1;
    }

    lx = strnlen(x, MAX_INPUT_LEN);
    ly = strnlen(y, MAX_INPUT_LEN);
    lz = strnlen(z, MAX_INPUT_LEN);

    if ((lx >= MAX_INPUT_LEN) || (ly >= MAX_INPUT_LEN) || (lz >= MAX_INPUT_LEN)) {
        return -1;
    }

    dp = (int ***)malloc((lx + 1U) * sizeof(int **));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0U; i <= lx; i++) {
        dp[i] = (int **)malloc((ly + 1U) * sizeof(int *));
        if (dp[i] == NULL) {
            for (j = 0U; j < i; j++) {
                for (k = 0U; k <= ly; k++) {
                    free(dp[j][k]);
                }
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
        for (j = 0U; j <= ly; j++) {
            dp[i][j] = (int *)malloc((lz + 1U) * sizeof(int));
            if (dp[i][j] == NULL) {
                for (k = 0U; k < j; k++) {
                    free(dp[i][k]);
                }
                free(dp[i]);
                for (k = 0U; k < i; k++) {
                    size_t m;
                    for (m = 0U; m <= ly; m++) {
                        free(dp[k][m]);
                    }
                    free(dp[k]);
                }
                free(dp);
                return -1;
            }
        }
    }

    for (i = 0U; i <= lx; i++) {
        for (j = 0U; j <= ly; j++) {
            for (k = 0U; k <= lz; k++) {
                if ((i == 0U) || (j == 0U) || (k == 0U)) {
                    dp[i][j][k] = 0;
                } else if ((x[i - 1U] == y[j - 1U]) && (x[i - 1U] == z[k - 1U])) {
                    dp[i][j][k] = dp[i - 1U][j - 1U][k - 1U] + 1;
                } else {
                    dp[i][j][k] = max3(dp[i - 1U][j][k], dp[i][j - 1U][k], dp[i][j][k - 1U]);
                }
            }
        }
    }

    result = dp[lx][ly][lz];

    for (i = 0U; i <= lx; i++) {
        for (j = 0U; j <= ly; j++) {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void)
{
    const char *s1 = "AGGT12";
    const char *s2 = "12TXAYB";
    const char *s3 = "12XBA";
    int length;

    length = lcs_of_three(s1, s2, s3);
    if (length < 0) {
        (void)fprintf(stderr, "Error computing LCS\n");
        return EXIT_FAILURE;
    }

    if (printf("Length of LCS of the three strings: %d\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}