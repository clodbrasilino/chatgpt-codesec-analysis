#include <stdio.h>

void sortMatrix(int matrix[][10], int rows, int columns) {
    int rowSum[10], temp, i, j;

    // Calculating sum of each row
    for (i = 0; i < rows; i++) {
        rowSum[i] = 0;
        for (j = 0; j < columns; j++) {
            rowSum[i] += matrix[i][j];
        }
    }

    // Sorting the matrix rows based on their sums using bubble sort
    for (i = 0; i < rows - 1; i++) {
        for (j = 0; j < rows - i - 1; j++) {
            if (rowSum[j] > rowSum[j + 1]) {
                // Swapping the rows
                for (int k = 0; k < columns; k++) {
                    temp = matrix[j][k];
                    matrix[j][k] = matrix[j + 1][k];
                    matrix[j + 1][k] = temp;
                }
                // Swapping the row sums
                temp = rowSum[j];
                rowSum[j] = rowSum[j + 1];
                rowSum[j + 1] = temp;
            }
        }
    }
}

int main() {
    int matrix[10][10], rows, columns;

    printf("Enter the number of rows (maximum 10): ");
    scanf("%d", &rows);

    printf("Enter the number of columns (maximum 10): ");
    scanf("%d", &columns);

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nMatrix before sorting:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    sortMatrix(matrix, rows, columns);

    printf("\nMatrix after sorting in ascending order based on sum of rows:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}