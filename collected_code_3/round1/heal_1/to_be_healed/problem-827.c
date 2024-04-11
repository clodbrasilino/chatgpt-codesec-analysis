#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int sum_column(int **matrix, int rows, int column) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += matrix[i][column];
    }
    return sum;
}

int main() {
    int rows = 3;
    int cols = 3;
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'matrix' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*matrix' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*matrix_42 + 8' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*matrix_42 + 16' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    matrix[2][0] = 7; matrix[2][1] = 8; matrix[2][2] = 9;

    int column_to_sum = 1;
    int sum = sum_column(matrix, rows, column_to_sum);
    printf("Sum of column %d is %d\n", column_to_sum, sum);

    for (int i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(matrix[i]);
    }
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(matrix);

    return 0;
}