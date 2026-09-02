#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'fmin'
  */

#define MAX_SIZE 200

int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    for (int row = triangleSize - 2; row >= 0; --row) {
        for (int col = 0; col <= row; ++col) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'fmin' [-Wimplicit-function-declaration]
             *  include the header <math.h> or explicitly provide a declaration for 'fmin'
             *  call to undeclared library function 'fmin' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            triangle[row][col] += fmin(triangle[row + 1][col], triangle[row + 1][col + 1]);
        }
    }
    return triangle[0][0];
}

int main() {
    int triangle[][MAX_SIZE] = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };
    int triangleSize = 4;
    int triangleColSize[] = {1, 2, 3, 4};

    int result = minimumTotal((int**)triangle, triangleSize, triangleColSize);
    printf("%d\n", result);

    return 0;
}