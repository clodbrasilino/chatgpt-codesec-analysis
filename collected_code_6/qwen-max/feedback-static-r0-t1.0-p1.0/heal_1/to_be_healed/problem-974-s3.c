#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'fmin'
  */

int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    if (triangleSize == 0) return 0;

    for (int i = triangleSize - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'fmin' [-Wimplicit-function-declaration]
             *  include the header <math.h> or explicitly provide a declaration for 'fmin'
             *  call to undeclared library function 'fmin' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            triangle[i][j] += fmin(triangle[i + 1][j], triangle[i + 1][j + 1]);
        }
    }
    return triangle[0][0];
}

int main() {
    int triangleSize;
    scanf("%d", &triangleSize);

    int **triangle = (int **)malloc(triangleSize * sizeof(int *));
    int *triangleColSize = (int *)malloc(triangleSize * sizeof(int));

    for (int i = 0; i < triangleSize; ++i) {
        triangleColSize[i] = i + 1;
        triangle[i] = (int *)malloc((i + 1) * sizeof(int));
        for (int j = 0; j <= i; ++j) {
            scanf("%d", &triangle[i][j]);
        }
    }

    int minPathSum = minimumTotal(triangle, triangleSize, triangleColSize);
    printf("%d\n", minPathSum);

    for (int i = 0; i < triangleSize; ++i) {
        free(triangle[i]);
    }
    free(triangle);
    free(triangleColSize);

    return 0;
}