#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int sumColumn(int **list, int rows, int col) {
    int sum = 0;
    for(int i = 0; i < rows; i++) {
        sum += list[i][col];
    }
    return sum;
}

int main() {
    int rows = 3;
    int cols = 3;
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    int **list = (int **)malloc(rows * sizeof(int *));
    for(int i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        list[i] = (int *)malloc(cols * sizeof(int));
    }

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*list_33 + _10 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            list[i][j] = i + j;
        }
    }

    int colToSum = 1;
    int sum = sumColumn(list, rows, colToSum);
    printf("Sum of column %d is %d\n", colToSum, sum);

    for(int i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  include '<stdlib.h>' or provide a declaration of 'free'
         */
        free(list[i]);
    }
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(list);

    return 0;
}