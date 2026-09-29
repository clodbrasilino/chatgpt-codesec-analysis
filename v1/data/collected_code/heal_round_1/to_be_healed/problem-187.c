#include <stdio.h>
#include <string.h>
 
int max(int a, int b);
 
void lcs(char *X, char *Y, int m, int n)
{
    int L[m + 1][n + 1];
    int i, j;
 
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            /* Possible weaknesses found:
             *  Cannot determine that 'X[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'Y[j-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
 
    int index = L[m][n];
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char lcs[index + 1];
    lcs[index] = '\0';
 
    i = m;
    j = n;
    while (i > 0 && j > 0) {
        /* Possible weaknesses found:
         *  Cannot determine that 'X[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'Y[j-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (X[i - 1] == Y[j - 1]) {
            /* Possible weaknesses found:
             *  Cannot determine that 'X[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
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
 
    /* Possible weaknesses found:
     *  Cannot determine that 'lcs[0]' is initialized [premium-bughuntingUninit]
     */
    printf("Longest Common Subsequence: %s", lcs);
}
 
int max(int a, int b)
{
    return (a > b) ? a : b;
}
 
int main()
{
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
 
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int m = strlen(X);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int n = strlen(Y);
 
    lcs(X, Y, m, n);
 
    return 0;
}