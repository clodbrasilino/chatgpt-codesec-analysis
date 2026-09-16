#include <stdio.h>
#include <stdlib.h>

int sum_column(int **list, int list_size, int column) {
    int sum = 0;
    for (int i = 0; i < list_size; ++i) {
        sum += list[i][column];
    }
    return sum;
}

int main() {
    int list_size = 4;
    /* Possible weaknesses found:
     *  Variable 'columns' is assigned a value that is never used. [unreadVariable]
     */
    int columns = 3;
    int array1[] = {1, 2, 3};
    int array2[] = {4, 5, 6};
    int array3[] = {7, 8, 9};
    int array4[] = {10, 11, 12};

    /* Possible weaknesses found:
     *  variable-sized object may not be initialized except with an empty initializer
     *  variable-sized object may not be initialized
     */
    int *list[list_size] = {array1, array2, array3, array4};

    int column_to_sum = 1;
    int result = sum_column(list, list_size, column_to_sum);

    printf("The sum of column %d is: %d\n", column_to_sum, result);

    return 0;
}