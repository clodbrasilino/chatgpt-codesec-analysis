#include<stdio.h>

int countWays(int n) {
    int A[n+1];
    A[0] = 1;
    A[1] = 0;
    A[2] = 3;
    for (int i = 3; i <= n; i++) {
        A[i] = A[i-2] * 4 - A[i-4];
    }
    return A[n];
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Number of ways to fill the board: %d", countWays(n));
    return 0;
}