#include<stdio.h>

int countWays(int n) {
    if(n<0) return 0;

    int A[n+1];
    A[0] = 1;
    if(n>0) A[1] = 0;
    if(n>1) A[2] = 3;

    for (int i = 3; i <= n; i++) {
        if(i > 3) A[i] = A[i-2] * 4 - A[i-4];
        else  A[i] = A[i-1] * 4;
    }
    return A[n];
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    if(n<0){
        printf("Invalid input! Please enter a non-negative number.");
        return -1;
    }
    
    printf("Number of ways to fill the board: %d", countWays(n));
    return 0;
}