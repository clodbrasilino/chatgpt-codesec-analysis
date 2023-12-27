#include<stdio.h>

int maxSumRectangularGrid(const int grid[], int n) {
    if (n <= 0) {
        return 0;
    }
    int inclusive = grid[0];
    int exclusive = 0;
    int temp;
    
    for (int i = 1; i < n; i++) {
        temp = inclusive;
        inclusive = (inclusive > exclusive + grid[i]) ? inclusive : exclusive + grid[i];
        exclusive = temp;
    }
    return (inclusive > exclusive) ? inclusive : exclusive;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if(scanf("%d", &n) != 1)
        return 1;

    int grid[2 * n];
    
    printf("Enter the elements of the grid: ");
    for (int i = 0; i < 2 * n; i++) {
        if(scanf("%d", &grid[i]) != 1)
            return 1;
    }
    
    int maxSum = maxSumRectangularGrid(grid, 2 * n);
    
    printf("Maximum sum using no adjacent numbers: %d\n", maxSum);
    
    return 0;
}