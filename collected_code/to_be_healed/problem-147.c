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
    /* Possible weaknesses found:
     *  Cannot determine that 'triangle[0][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    return triangle[0][0];
}

int main() {
    int triangle[MAX][MAX];
    int n;
    printf("Enter the number of rows: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
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