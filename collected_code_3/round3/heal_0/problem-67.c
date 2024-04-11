#include <stdio.h>

#define MAX 100

unsigned long long int bell[MAX][MAX];

unsigned long long int bellNumber(int n) {
    bell[0][0] = 1;
    for (int i=1; i<=n; i++) {
        bell[i][0] = bell[i-1][i-1];
        for (int j=1; j<=i; j++) {
            bell[i][j] = bell[i-1][j-1] + bell[i][j-1];
        }
    }
    return bell[n][0];
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Bell number is: %llu\n", bellNumber(n));
    return 0;
}