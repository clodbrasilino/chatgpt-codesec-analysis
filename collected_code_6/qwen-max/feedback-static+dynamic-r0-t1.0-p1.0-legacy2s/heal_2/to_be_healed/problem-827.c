#include <stdio.h>
#include <stdlib.h>

int sum_column(int **list, int rows, int cols, int col_index) {
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
        sum += list[i][col_index];
    }
    return sum;
}

int main() {
    int rows = 3;
    int cols = 4;

    /* Possible weaknesses found:
     *  variable-sized object may not be initialized
     *  variable-sized object may not be initialized except with an empty initializer
     */
    int data1[cols] = {1, 2, 3, 4};
    /* Possible weaknesses found:
     *  variable-sized object may not be initialized
     *  variable-sized object may not be initialized except with an empty initializer
     */
    int data2[cols] = {5, 6, 7, 8};
    /* Possible weaknesses found:
     *  variable-sized object may not be initialized
     *  variable-sized object may not be initialized except with an empty initializer
     */
    int data3[cols] = {9, 10, 11, 12};

    int *list[rows];
    list[0] = data1;
    list[1] = data2;
    list[2] = data3;

    int col_index = 2;
    int result = sum_column(list, rows, cols, col_index);

    printf("Sum of column %d: %d\n", col_index, result);

    return 0;
}