#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void removeColumn(int list[MAX_ROWS][MAX_COLS], int num_rows, int num_cols, int column) 
{
    if (column >= num_cols) {
        printf("Invalid column\n");
        return;
    }

    for (int i = 0; i < num_rows; i++) {
        for (int j = column; j < num_cols - 1; j++) {
            list[i][j] = list[i][j + 1];
        }
    }
}

int main() 
{
    int list[MAX_ROWS][MAX_COLS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int num_rows = 3;
    int num_cols = 3;
    int column = 1;

    removeColumn(list, num_rows, num_cols, column);

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols - 1; j++) {
            printf("%d ", list[i][j]);
        }
        printf("\n");
    }

    return 0;
}