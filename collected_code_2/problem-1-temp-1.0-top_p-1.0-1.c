#include<stdio.h>
#include<limits.h>

#define R 3
#define C 3

int min(int x, int y, int z);
  
int minCost(int cost[R][C], int m, int n) {
    int i, j;
    int total_cost[R][C];

    total_cost[0][0] = cost[0][0];
 
    for(i = 1; i <= m; i++)
        total_cost[i][0] = total_cost[i-1][0] + cost[i][0];

    for(j = 1; j <= n; j++)
        total_cost[0][j] = total_cost[0][j-1] + cost[0][j];

    for(i = 1; i <= m; i++)
        for(j = 1; j <= n; j++)
            total_cost[i][j] = min(total_cost[i-1][j-1], total_cost[i-1][j], total_cost[i][j-1]) + cost[i][j];
    
    return total_cost[m][n];
}
 
int min(int x, int y, int z) {
   if(x < y)
      return (x < z)? x : z;
   else
      return (y < z)? y : z;
}

int main() {
   int cost[R][C] = { {1, 2, 3}, 
                      {4, 8, 2}, 
                      {1, 5, 3} };

   printf("minimum cost to reach (2, 2) is %d \n", minCost(cost, 2, 2));

   return 0;
}
