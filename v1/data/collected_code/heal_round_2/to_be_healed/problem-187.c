#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b);

void lcs(const char *X, const char *Y, size_t m, size_t n)
{
    int **L = malloc((m + 1) * sizeof(int *));
    for (size_t i = 0; i <= m; i++){
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'L' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        L[i] = calloc(n + 1, sizeof(int));
    }
    
    size_t i, j;
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL '*L_103 + _7 + j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    
    /* Possible weaknesses found:
     *  use of uninitialized value '*L_103 + _52' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
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
 
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t m = strlen(X);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t n = strlen(Y);
 
    lcs(X, Y, m, n);
 
    return 0;
}