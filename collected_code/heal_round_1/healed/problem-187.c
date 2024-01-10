#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b);

void lcs(const char *X, const char *Y, size_t m, size_t n)
{
    int **L = malloc((m + 1) * sizeof(int *));
    for (size_t i = 0; i <= m; i++){
        L[i] = calloc(n + 1, sizeof(int));
    }
    
    size_t i, j;
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    
    size_t index = L[m][n];
    char *lcs = calloc(index + 1, sizeof(char));
        
    i = m;
    j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }
    
    printf("Longest Common Subsequence: %s", lcs);
    
    free(lcs);
    for (i = 0; i <= m; i++){
        free(L[i]);
    }
    free(L);
}
 
int max(int a, int b)
{
    return (a > b) ? a : b;
}
 
int main()
{
    const char X[] = "AGGTAB";
    const char Y[] = "GXTXAYB";
 
    size_t m = strlen(X);
    size_t n = strlen(Y);
 
    lcs(X, Y, m, n);
 
    return 0;
}