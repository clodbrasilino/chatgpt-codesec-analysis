#include <stdio.h>
#include <limits.h>

#define MAX 100000

int dp[MAX]; 
  
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
            /* Possible weaknesses found:
             *  implicit declaration of function 'min' [-Wimplicit-function-declaration]
             */
            dp[n] = min(dp[n], 1+minSquares(n-temp));
    }
    return dp[n];
}

int main() 
{ 
    int n;
    printf("Enter a number");
    scanf("%d", &n);

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'N' undeclared (first use in this function)
     */
    for(int i=0; i<=N; i++)
        dp[i] = INT_MAX;
  
    dp[0] = 0, dp[1] = 1, dp[2] = 2, dp[3] = 3;
    
    printf("Minimum number of squares: %d", minSquares(n));
    return 0;
} 