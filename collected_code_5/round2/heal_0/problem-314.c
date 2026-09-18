#include <stdio.h>

int max(int a, int b) { 
    return a > b ? a : b; 
}

int findMaxSum(int grid[][2], int n) {
    
    int incl = grid[0][0];
    int excl = 0;
    int excl_new;
    int i;
 
    for (i = 1; i < n; i++) {
         excl_new = (incl > excl) ? incl : excl;
         incl = excl + max(grid[i][0], grid[i][1]);
         excl = excl_new;
    }
    return ((incl > excl) ? incl : excl);
}

int main() {
    int grid[][2] = {{1, 2}, {9, 10}, {15, 1}, {5, 6}, {3, 100}, {12, 2}};
    int n = sizeof(grid) / sizeof(grid[0]);
    printf("Maximum sum such that no two numbers are adjacent %d \n", findMaxSum(grid, n));
    return 0;
}