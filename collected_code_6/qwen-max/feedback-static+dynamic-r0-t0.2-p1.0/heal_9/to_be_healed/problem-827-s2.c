#include <stdio.h>
#include <stdlib.h>

int sum_column(int (*list)[3], int rows, int col_index) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += list[i][col_index];
    }
    return sum;
}

int main() {
    int rows = 4;
    int cols = 3;
    /* Possible weaknesses found:
     *  variable-sized object may not be initialized except with an empty initializer
     *  variable-sized object may not be initialized
     */
    int data[rows][cols] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    int (*list)[cols] = malloc(rows * sizeof(*list));
    if (list == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            list[i][j] = data[i][j];
        }
    }

    int col_index = 1;
    int result = sum_column(list, rows, col_index);
    printf("Sum of column %d: %d\n", col_index, result);

    free(list);

    return 0;
}