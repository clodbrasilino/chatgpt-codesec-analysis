#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void removeSimilarRows(int matrix[MAX_ROWS][MAX_COLS], int *numRows, int numCols) {
    int distinctRows[MAX_ROWS][MAX_COLS];
    int distinctCount = 0;

    // Check each row for uniqueness
    for (int i = 0; i < *numRows; i++) {
        int isUnique = 1;

        // Compare current row with previous distinct rows
        for (int j = 0; j < distinctCount; j++) {
            int isSame = 1;

            // Compare each element of the rows
            for (int k = 0; k < numCols; k++) {
                if (matrix[i][k] != distinctRows[j][k]) {
                    isSame = 0;
                    break;
                }
            }

            // If rows are the same, mark it as not unique
            if (isSame) {
                isUnique = 0;
                break;
            }
        }

        // If row is unique, add it to distinctRows matrix
        if (isUnique) {
            for (int k = 0; k < numCols; k++) {
                distinctRows[distinctCount][k] = matrix[i][k];
            }
            distinctCount++;
        }
    }

    // Copy distinctRows back to matrix
    for (int i = 0; i < distinctCount; i++) {
        for (int j = 0; j < numCols; j++) {
            matrix[i][j] = distinctRows[i][j];
        }
    }

    *numRows = distinctCount;
}

int main() {
    int matrix[MAX_ROWS][MAX_COLS];
    int numRows, numCols;

    printf("Enter the number of rows: ");
    scanf("%d", &numRows);
    printf("Enter the number of columns: ");
    scanf("%d", &numCols);

    printf("Enter the matrix elements row by row:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    removeSimilarRows(matrix, &numRows, numCols);

    printf("Matrix after removing similar rows:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}