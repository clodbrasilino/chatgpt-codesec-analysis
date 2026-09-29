#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

void flattenMatrix(int rows, int cols, Tuple matrix[rows][cols], Tuple *result) {
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            result[j * rows + i].x = matrix[i][j].x;
            result[j * rows + i].y = matrix[i][j].y;
        }
    }
}

int main() {
    int rows = 3;
    int cols = 4;
    Tuple matrix[3][4] = {{{1, 2}, {3, 4}, {5, 6}, {7, 8}},
                          {{9, 10}, {11, 12}, {13, 14}, {15, 16}},
                          {{17, 18}, {19, 20}, {21, 22}, {23, 24}}};
    Tuple *result = (Tuple *)malloc(rows * cols * sizeof(Tuple));
    
    if (result == NULL) {
        return 1;
    }
    
    flattenMatrix(rows, cols, matrix, result);
    
    for (int i = 0; i < rows * cols; ++i) {
        printf("(%d, %d) ", result[i].x, result[i].y);
    }
    
    free(result);
    return 0;
}