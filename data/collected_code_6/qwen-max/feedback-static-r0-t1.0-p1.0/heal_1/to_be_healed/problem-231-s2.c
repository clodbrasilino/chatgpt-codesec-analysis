#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int findMaxSum(int **triangle, int n) {
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            triangle[i][j] += (triangle[i + 1][j] > triangle[i + 1][j + 1]) ? triangle[i + 1][j] : triangle[i + 1][j + 1];
        }
    }
    return triangle[0][0];
}

int main() {
    int n;
    scanf("%d", &n);
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    int **triangle = (int **)malloc(n * sizeof(int *));
    if (triangle == NULL) return 1;

    for (int i = 0; i < n; ++i) {
        triangle[i] = (int *)malloc((i + 1) * sizeof(int));
        if (triangle[i] == NULL) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
             *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
             *  include '<stdlib.h>' or provide a declaration of 'free'
             */
            for (int k = 0; k < i; ++k) free(triangle[k]);
            free(triangle);
            return 1;
        }
        for (int j = 0; j <= i; ++j) {
            scanf("%d", &triangle[i][j]);
        }
    }

    int maxSum = findMaxSum(triangle, n);

    for (int i = 0; i < n; ++i) {
        free(triangle[i]);
    }
    free(triangle);

    printf("%d\n", maxSum);
    return 0;
}