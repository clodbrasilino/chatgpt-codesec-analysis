#include<stdio.h>

int maxSumRectangularGrid(int grid[], int n) {
    if (n <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     *  Cannot determine that 'grid[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int inclusive = grid[0];
    int exclusive = 0;
    int temp;
    
    for (int i = 1; i < n; i++) {
        temp = inclusive;
        /* Possible weaknesses found:
         *  Cannot determine that 'grid[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        inclusive = (inclusive > exclusive + grid[i]) ? inclusive : exclusive + grid[i];
        exclusive = temp;
    }
    return (inclusive > exclusive) ? inclusive : exclusive;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    int grid[2 * n];
    
    printf("Enter the elements of the grid: ");
    for (int i = 0; i < 2 * n; i++) {
        scanf("%d", &grid[i]);
    }
    
    int maxSum = maxSumRectangularGrid(grid, 2 * n);
    
    printf("Maximum sum using no adjacent numbers: %d\n", maxSum);
    
    return 0;
}