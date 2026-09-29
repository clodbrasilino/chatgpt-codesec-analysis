#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef Point* PointList[6];

PointList* calculateHexagonGrid(int rows, int cols, double size) {
    PointList* hexGrid = (PointList*)malloc(rows * cols * sizeof(PointList));
    if (hexGrid == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            /* Possible weaknesses found:
             *  cast specifies array type
             *  used type 'PointList' (aka 'Point *[6]') where arithmetic or pointer type is required
             */
            hexGrid[i * cols + j] = (PointList)malloc(6 * sizeof(Point*));
            if (hexGrid[i * cols + j] == NULL) {
                for (int k = 0; k < i * cols + j; ++k) {
                    free(hexGrid[k]);
                }
                free(hexGrid);
                return NULL;
            }
            for (int k = 0; k < 6; ++k) {
                hexGrid[i * cols + j][k] = (Point*)malloc(sizeof(Point));
                if (hexGrid[i * cols + j][k] == NULL) {
                    for (int l = 0; l < k; ++l) {
                        free(hexGrid[i * cols + j][l]);
                    }
                    free(hexGrid[i * cols + j]);
                    for (int m = 0; m < i * cols + j; ++m) {
                        for (int n = 0; n < 6; ++n) {
                            free(hexGrid[m][n]);
                        }
                        free(hexGrid[m]);
                    }
                    free(hexGrid);
                    return NULL;
                }
            }
            
            double y_offset = i * (size * 1.5) + ((j % 2) ? (size * 0.75) : 0);
            double x_offset = j * size * 1.5;
            hexGrid[i * cols + j][0]->x = x_offset;
            hexGrid[i * cols + j][0]->y = y_offset;
            hexGrid[i * cols + j][1]->x = x_offset + size * 0.5;
            hexGrid[i * cols + j][1]->y = y_offset - (size * 0.866);
            hexGrid[i * cols + j][2]->x = x_offset + size * 1.5;
            hexGrid[i * cols + j][2]->y = y_offset;
            hexGrid[i * cols + j][3]->x = x_offset + size * 1.5;
            hexGrid[i * cols + j][3]->y = y_offset + (size * 0.866);
            hexGrid[i * cols + j][4]->x = x_offset + size * 0.5;
            hexGrid[i * cols + j][4]->y = y_offset + (size * 1.732);
            hexGrid[i * cols + j][5]->x = x_offset;
            hexGrid[i * cols + j][5]->y = y_offset + (size * 0.866);
        }
    }
    return hexGrid;
}

void printHexagonGrid(PointList* hexGrid, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("Hexagon at (%d, %d):\n", i, j);
            for (int k = 0; k < 6; ++k) {
                printf("  Vertex %d: (%.2f, %.2f)\n", k, hexGrid[i * cols + j][k]->x, hexGrid[i * cols + j][k]->y);
            }
        }
    }
}

void freeHexagonGrid(PointList* hexGrid, int rows, int cols) {
    for (int i = 0; i < rows * cols; ++i) {
        for (int j = 0; j < 6; ++j) {
            free(hexGrid[i][j]);
        }
        free(hexGrid[i]);
    }
    free(hexGrid);
}

int main() {
    int rows = 2;
    int cols = 3;
    double size = 2.0;
    
    PointList* hexGrid = calculateHexagonGrid(rows, cols, size);
    if (hexGrid != NULL) {
        printHexagonGrid(hexGrid, rows, cols);
        freeHexagonGrid(hexGrid, rows, cols);
    } else {
        printf("Memory allocation failed.\n");
    }
    
    return 0;
}