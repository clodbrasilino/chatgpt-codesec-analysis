#include <stdio.h>
#define MAX 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxPathSum(int triangle[MAX][MAX], int n) {
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            triangle[i][j] += max(triangle[i+1][j], triangle[i+1][j+1]);
        }
    }
    return triangle[0][0];
}

int main() {
    int triangle[MAX][MAX];
    int n = 0;

    printf("Enter the number of rows: ");
    scanf("%d", &n);
	
	printf("Enter the elements of the triangle:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }
   
    int result = maxPathSum(triangle, n);
    printf("Maximum total path sum is: %d\n", result);
    return 0;
}