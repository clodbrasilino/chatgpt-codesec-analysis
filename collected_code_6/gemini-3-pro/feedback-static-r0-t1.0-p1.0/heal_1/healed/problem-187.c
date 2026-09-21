#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

int str_len_bounded(const char *str, int max_len) {
    int len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

char* lcs(const char* X, const char* Y) {
    if (!X || !Y) return NULL;

    int m = str_len_bounded(X, MAX_STR_LEN);
    int n = str_len_bounded(Y, MAX_STR_LEN);

    if (m == 0 || n == 0) {
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    int** L = (int**)malloc((m + 1) * sizeof(int*));
    if (!L) return NULL;

    for (int i = 0; i <= m; i++) {
        L[i] = (int*)calloc((n + 1), sizeof(int));
        if (!L[i]) {
            for (int j = 0; j < i; j++) {
                free(L[j]);
            }
            free(L);
            return NULL;
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    int index = L[m][n];
    char* lcs_str = (char*)malloc(index + 1);
    if (!lcs_str) {
        for (int i = 0; i <= m; i++) {
            free(L[i]);
        }
        free(L);
        return NULL;
    }

    lcs_str[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs_str[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    for (int k = 0; k <= m; k++) {
        free(L[k]);
    }
    free(L);

    return lcs_str;
}

int main(void) {
    const char* str1 = "AGGTAB";
    const char* str2 = "GXTXAYB";

    char* result = lcs(str1, str2);

    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed or invalid input.\n");
    }

    return 0;
}