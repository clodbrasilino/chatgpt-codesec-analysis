#include <stdio.h>
#include <limits.h>

#define ROWS 4
#define COLS 3

int findMaxInColumn(int tuples[ROWS][COLS], int rows, int cols, int n) {
    if (tuples == NULL || rows <= 0 || cols <= 0 || n < 0 || n >= cols) {
        return INT_MIN;
    }

    int max_val = tuples[0][n];

    for (int i = 1; i < rows; i++) {
        if (tuples[i][n] > max_val) {
            max_val = tuples[i][n];
        }
    }

    return max_val;
}

int main(void) {
    int tuples[ROWS][COLS] = {
        {10, 20, 30},
        {15, 25, 5},
        {8, 50, 40},
        {12, 18, 22}
    };

    int target_col = 1; 

    int max_val = findMaxInColumn(tuples, ROWS, COLS, target_col);

    if (max_val != INT_MIN) {
        printf("Maximum value in column %d is %d\n", target_col, max_val);
    } else {
        printf("Invalid input or column index out of bounds.\n");
    }

    return 0;
}