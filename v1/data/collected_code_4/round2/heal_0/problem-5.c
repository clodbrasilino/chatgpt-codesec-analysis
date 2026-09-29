#include <stdio.h>

long int calculateWays(int n){
    long int dp[n+1];
    int i;

    dp[0] = 1; 
    dp[1] = 1;
    for(i=2; i<=n; i++){
        dp[i] = dp[i-1] + 2*dp[i-2];
    }
    return dp[n];
}

int main(){
    int n;
    printf("Enter the length of the board: ");
    scanf("%d", &n);
    if(n < 0){
        printf("Invalid Input.");
        return 0;
    }
    printf("Number of ways to fill the 3x%d board: %ld\n", n, calculateWays(n));
    return 0;
}