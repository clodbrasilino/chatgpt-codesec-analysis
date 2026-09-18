#include <stdio.h>

long long int countWays(int n, int m) {
    long long int count[n+1];
    
    int i;
    for (i = 0; i <= n; i++) {
        if (i < m)
            count[i] = 1;
        else if (i == m)
            count[i] = 2;
        else
            count[i] = count[i - 1] + count[i - m];
    }

    return count[n];
}

int main(void) {
    int n = 7, m = 2;
    printf("Number of ways = %lld", countWays(n, m));

    return 0;
}