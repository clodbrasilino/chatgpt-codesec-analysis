#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int sum_column(int **list, int num_lists, int list_length, int column) {
    int sum = 0;
    for (int i = 0; i < num_lists; i++) {
        sum += list[i][column];
    }
    return sum;
}

int main() {
    int num_lists = 3;
    int list_length = 4;
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    int **list = malloc(num_lists * sizeof(int *));
    for (int i = 0; i < num_lists; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        list[i] = malloc(list_length * sizeof(int));
        for (int j = 0; j < list_length; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*list_31 + _10 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            list[i][j] = i + j;
        }
    }

    int column_to_sum = 2;
    int sum = sum_column(list, num_lists, list_length, column_to_sum);
    printf("Sum of column %d is %d\n", column_to_sum, sum);

    for (int i = 0; i < num_lists; i++) {
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
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