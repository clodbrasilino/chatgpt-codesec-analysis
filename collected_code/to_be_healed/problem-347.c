#include <stdio.h>

int countSquares(int rows, int columns) {
    int total;
    total = rows * columns;
    return total;
}

int main() {
    int rows, columns, squares;
    printf("Enter the number of rows in the rectangle: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'rows' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &rows);
    printf("Enter the number of columns in the rectangle: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'columns' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &columns);
    squares = countSquares(rows, columns);
    printf("The number of squares in the rectangle is: %d\n", squares);
    return 0;
}