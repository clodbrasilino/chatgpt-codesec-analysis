#include <stdio.h>

int findMaxSum(int triangle[100][100], int rows) {
    int maxSum = 0;
    int i, j;

    for (i = rows - 2; i >= 0; i--) {
        for (j = 0; j <= i; j++) {
            triangle[i][j] += triangle[i + 1][j] > triangle[i + 1][j + 1] ? triangle[i + 1][j] : triangle[i + 1][j + 1];
        }
    }

    if(rows > 0)
        return triangle[0][0];
    else
        return maxSum;
}

int main() {
    int triangle[100][100];
    int rows = 0;
    int i, j;

    printf("Enter the number of rows in the triangle: ");
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