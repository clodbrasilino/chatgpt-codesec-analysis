#include <stdio.h>
#include <string.h>

#define MAX 100

int dp[MAX][MAX][MAX];

int max(int a, int b, int c) {
    return (a > b)? ((a > c)? a: c) : ((b > c)? b : c);
}

int lcs3(char *X, char *Y, char *Z, int m, int n, int o) {
    if(m == 0 || n == 0 || o == 0)
        return 0;

    if(dp[m][n][o] != -1)
        return dp[m][n][o];
    else {
        if(X[m-1] == Y[n-1] && X[m-1] == Z[o-1])
            return dp[m][n][o] = 1 + lcs3(X, Y, Z, m-1, n-1, o-1);
        else
            return dp[m][n][o] = max(lcs3(X, Y, Z, m-1, n, o), lcs3(X, Y, Z, m, n-1, o), lcs3(X, Y, Z, m, n, o-1));
    }
}

int main() {
    char X[MAX], Y[MAX], Z[MAX];
    
    printf("\nEnter the first string : ");
    fgets(X, MAX, stdin);

    printf("\nEnter the second string : ");
    fgets(Y, MAX, stdin);

    printf("\nEnter the third string : ");
    fgets(Z, MAX, stdin);

    int m = strlen(X)-1;
    int n = strlen(Y)-1;
    int o = strlen(Z)-1;

    memset(dp, -1, sizeof(dp));

    printf("\nLength of LCS is %d\n", lcs3(X, Y, Z, m, n, o));

    return 0;
}