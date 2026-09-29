#include <stdio.h>
#include <limits.h>

#define MAX 100000

int dp[MAX]; 

int min(int a, int b) {
    return (a < b) ? a : b;
}

int minSquares(int n) 
{ 
    if(n<=3)
        return n;
    
    if(dp[n] != INT_MAX) 
        return dp[n];
  
    for(int i=1; i*i<=n; i++){ 
        int temp = i*i; 
        if(temp>n)
            break;
        else 
            dp[n] = min(dp[n], 1+minSquares(n-temp));
    }
    return dp[n];
}

int main() 
{ 
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    for(int i=0; i<=n; i++)
        dp[i] = INT_MAX;
  
    dp[0] = 0, dp[1] = 1, dp[2] = 2, dp[3] = 3;
    
    printf("Minimum number of squares: %d\n", minSquares(n));
    return 0;
}