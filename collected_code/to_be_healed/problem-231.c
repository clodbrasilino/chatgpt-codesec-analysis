#include <stdio.h>

int findMaxSum(int triangle[100][100], int rows) {
    int maxSum = 0;
    int i, j;
    
    // Start from the second last row
    for (i = rows - 2; i >= 0; i--) {
        for (j = 0; j <= i; j++) {
            // Calculate the maximum sum for each position
            triangle[i][j] += triangle[i + 1][j] > triangle[i + 1][j + 1] ? triangle[i + 1][j] : triangle[i + 1][j + 1]; 
        }
    }
    
    // The maximum sum will be at the top of the triangle
    /* Possible weaknesses found:
     *  Cannot determine that 'triangle[0][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    return triangle[0][0];
}

int main() {
    int triangle[100][100];
    int rows, i, j;
    
    printf("Enter the number of rows in the triangle: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'rows' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &rows);
    
    printf("Enter the numbers:\n");
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }
    
    int maxSum = findMaxSum(triangle, rows);
    
    printf("The maximum sum in the given right triangle of numbers is: %d\n", maxSum);
    
    return 0;
}