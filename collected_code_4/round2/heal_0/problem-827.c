#include <stdio.h>

int sum_column(int **lists, int numOfLists, int column) {
    if (column < 0) {
        printf("Error: Invalid column number.\n");
        return -1;
    }

    int i, sum = 0;
    for (i = 0; i < numOfLists; ++i) {
        if (lists[i] == NULL) {
            printf("Error: Null list at index %d.\n", i);
            return -1;
        }
        sum += lists[i][column];
    }

    return sum;
}

int main() {
    const int ROW = 4;
    const int COL = 3;

    int *array[ROW];
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int arr3[] = {7, 8, 9};
    int arr4[] = {10, 11, 12};

    array[0] = arr1;
    array[1] = arr2;
    array[2] = arr3;
    array[3] = arr4;

    int sum = sum_column(array, ROW, 1);
    if (sum >= 0) {
        printf("Sum of column 1: %d\n", sum);
    }

    return 0;
}