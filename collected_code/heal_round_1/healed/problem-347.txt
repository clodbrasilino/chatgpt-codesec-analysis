#include <stdio.h>

int countSquares(int rows, int columns) {
    int total;
    total = rows * columns;
    return total;
}

int main() {
    int rows = 0, columns = 0, squares = 0;
    printf("Enter the number of rows in the rectangle: ");
    scanf("%d", &rows);
    printf("Enter the number of columns in the rectangle: ");
    scanf("%d", &columns);
    squares = countSquares(rows, columns);
    printf("The number of squares in the rectangle is: %d\n", squares);
    return 0;
}