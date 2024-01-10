#include <stdio.h>

int sumColumn(int list[][3], int numRows, int column) {
    int sum = 0;
    for (int i = 0; i < numRows; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i][column]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum += list[i][column];
    }
    return sum;
}

int main() {
    int list[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    int numRows = 4;
    int column = 1;
    int result = sumColumn(list, numRows, column);
    printf("Sum of column %d: %d\n", column, result);

    return 0;
}