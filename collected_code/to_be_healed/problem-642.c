#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void removeSimilarRows(int matrix[MAX_ROWS][MAX_COLS], int *numRows, int numCols) {
    int distinctRows[MAX_ROWS][MAX_COLS];
    int distinctCount = 0;

    // Check each row for uniqueness
    /* Possible weaknesses found:
     *  Cannot determine that '*numRows' is initialized [premium-bughuntingUninit]
     */
    for (int i = 0; i < *numRows; i++) {
        int isUnique = 1;

        // Compare current row with previous distinct rows
        for (int j = 0; j < distinctCount; j++) {
            int isSame = 1;

            // Compare each element of the rows
            for (int k = 0; k < numCols; k++) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'matrix[i][k]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'distinctRows[j][k]' is initialized [premium-bughuntingUninit]
                 */
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
                /* Possible weaknesses found:
                 *  Cannot determine that 'matrix[i][k]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                distinctRows[distinctCount][k] = matrix[i][k];
            }
            distinctCount++;
        }
    }

    // Copy distinctRows back to matrix
    for (int i = 0; i < distinctCount; i++) {
        for (int j = 0; j < numCols; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'distinctRows[i][j]' is initialized [premium-bughuntingUninit]
             */
            matrix[i][j] = distinctRows[i][j];
        }
    }

    *numRows = distinctCount;
}

int main() {
    int matrix[MAX_ROWS][MAX_COLS];
    int numRows, numCols;

    printf("Enter the number of rows: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'numRows' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &numRows);
    printf("Enter the number of columns: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'numCols' is initialized [premium-bughuntingUninit]
     */
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
            /* Possible weaknesses found:
             *  Cannot determine that 'matrix[i][j]' is initialized [premium-bughuntingUninit]
             */
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}