#include <stdio.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/* Possible weaknesses found:
 *  array type has incomplete element type 'int[]'
 *  declaration of 'matrix' as multidimensional array must have bounds for all dimensions except the first
 */
int findMaxSum(int matrix[2][], int n) {
    int incl = MAX(matrix[0][0], matrix[1][0]);
    int excl = 0;
    int exclNew;
    int i;

    for (i = 1; i < n; i++) {
        exclNew = (incl > excl) ? incl : excl;
        incl = excl + MAX(matrix[0][i], matrix[1][i]);
        excl = exclNew;
    }
    return ((incl > excl) ? incl : excl);
}

int main() {
    int matrix[2][4] = {{1, 2, 9, 5}, {5, 8, 4, 1}};
    int n = sizeof(matrix[0]) / sizeof(matrix[0][0]);
    /* Possible weaknesses found:
     *  type of formal parameter 1 is incomplete
     */
    printf("%d\n", findMaxSum(matrix, n));
    return 0;
}