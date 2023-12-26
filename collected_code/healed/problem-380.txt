#include <stdio.h>

void generateArray(int numRows, int numCols, int array[numRows][numCols]) {
    int count = 1;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            array[i][j] = count++;
        }
    }
}

int main() {
    int numRows = 3;
    int numCols = 4;
    int array[numRows][numCols];

    generateArray(numRows, numCols, array);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    return 0;
}