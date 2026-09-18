#include<stdio.h>
#include<limits.h>

int maxProfit(int price[], int n, int k)
{
    int profit[k+1][n+1];
 
    for (int i = 0; i <= k; i++)
        profit[i][0] = 0;
 
    for (int j= 0; j<=n; j++)
        profit[0][j] = 0;
 
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j < n; j++) {
            int max_so_far = INT_MIN;
 
            for (int m = 0; m < j; m++)
                /* Possible weaknesses found:
                 *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
                 */
                max_so_far = max(max_so_far, price[j] - price[m] + profit[i-1][m]);
                
            profit[i][j] = max(profit[i][j-1], max_so_far);
        }
    }
 
    return profit[k][n-1];
}
 
int max(int x, int y)
{
    return y > x ? y : x;
}
 
int main()
{
    int k = 2;
    int price[] = {10, 22, 5, 75, 65, 80};
    int n = sizeof(price)/sizeof(price[0]);
 
    printf("Maximum profit is %d", maxProfit(price, n, k));
 
    return 0;
}