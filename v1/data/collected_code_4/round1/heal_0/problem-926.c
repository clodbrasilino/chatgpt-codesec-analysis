#include <stdio.h>

#define MAX 100

long long dp[MAX][MAX];

long long factorial(int n) {
    long long fact = 1;
    for(int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

long long rencontreNumber(int n, int m) {
    if (n == 0 && m == 0) {
        return 1;
    }
    if (n == 0 || m == 0) {
        return 0;
    }    

    if (dp[n][m] != -1) {
        return dp[n][m];
    }

    return dp[n][m] = ((n - 1) * rencontreNumber(n - 1, m) + rencontreNumber(n - 1, m - 1));
}

int main() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            dp[i][j] = -1;
        }
    }
    
    int n, m;
    printf("Enter the total number of elements: ");
    scanf("%d", &n);
    printf("Enter the number of misplaced elements: ");
    scanf("%d", &m);

    long long res = rencontreNumber(n, m);
    res = (res * factorial(n)) / factorial(n - m);

    printf("The %d-th rencontre number is: %lld\n", n, res);

    return 0;
}