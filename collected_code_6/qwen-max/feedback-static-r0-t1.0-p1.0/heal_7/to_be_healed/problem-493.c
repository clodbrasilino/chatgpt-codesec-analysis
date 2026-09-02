#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef Point (*PointList)[6];

PointList* calculateHexagonGrid(int rows, int cols, double size) {
    PointList* hexGrid = malloc(rows * cols * sizeof(PointList));
    if (hexGrid == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            hexGrid[i * cols + j] = malloc(sizeof(Point[6]));
            if (hexGrid[i * cols + j] == NULL) {
                for (int k = 0; k < i * cols + j; ++k) {
                    free(hexGrid[k]);
                }
                free(hexGrid);
                return NULL;
            }
            for (int k = 0; k < 6; ++k) {
                /* Possible weaknesses found:
                 *  member reference base type 'Point[6]' is not a structure or union
                 *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + (sizetype)((long unsigned int)k * 96))' is a pointer; did you mean to use '->'?
                 */
                hexGrid[i * cols + j][k].x = 0.0;
                /* Possible weaknesses found:
                 *  member reference base type 'Point[6]' is not a structure or union
                 *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + (sizetype)((long unsigned int)k * 96))' is a pointer; did you mean to use '->'?
                 */
                hexGrid[i * cols + j][k].y = 0.0;
            }
            
            double y_offset = i * (size * 1.5) + ((j % 2) ? (size * 0.75) : 0);
            double x_offset = j * size * 1.5;

            /* Possible weaknesses found:
             *  member reference base type 'Point[6]' is not a structure or union
             *  '(Point *)*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8))' is a pointer; did you mean to use '->'?
             */
            hexGrid[i * cols + j][0].x = x_offset;
            /* Possible weaknesses found:
             *  member reference base type 'Point[6]' is not a structure or union
             *  '(Point *)*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8))' is a pointer; did you mean to use '->'?
             */
            hexGrid[i * cols + j][0].y = y_offset;
            /* Possible weaknesses found:
             *  member reference base type 'Point[6]' is not a structure or union
             *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + 96)' is a pointer; did you mean to use '->'?
             */
            hexGrid[i * cols + j][1].x = x_offset + size * 0.5;
            /* Possible weaknesses found:
             *  member reference base type 'Point[6]' is not a structure or union
             *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + 96)' is a pointer; did you mean to use '->'?
             */
            hexGrid[i * cols + j][1].y = y_offset - (size * 0.866);
            /* Possible weaknesses found:
             *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + 192)' is a pointer; did you mean to use '->'?
             *  member reference base type 'Point[6]' is not a structure or union
             */
            hexGrid[i * cols + j][2].x = x_offset + size * 1.5;
            /* Possible weaknesses found:
             *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + 192)' is a pointer; did you mean to use '->'?
             *  member reference base type 'Point[6]' is not a structure or union
             */
            hexGrid[i * cols + j][2].y = y_offset;
            /* Possible weaknesses found:
             *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + 288)' is a pointer; did you mean to use '->'?
             *  member reference base type 'Point[6]' is not a structure or union
             */
            hexGrid[i * cols + j][3].x = x_offset + size * 1.5;
            /* Possible weaknesses found:
             *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + 288)' is a pointer; did you mean to use '->'?
             *  member reference base type 'Point[6]' is not a structure or union
             */
            hexGrid[i * cols + j][3].y = y_offset + (size * 0.866);
            /* Possible weaknesses found:
             *  member reference base type 'Point[6]' is not a structure or union
             *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + 384)' is a pointer; did you mean to use '->'?
             */
            hexGrid[i * cols + j][4].x = x_offset + size * 0.5;
            /* Possible weaknesses found:
             *  member reference base type 'Point[6]' is not a structure or union
             *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + 384)' is a pointer; did you mean to use '->'?
             */
            hexGrid[i * cols + j][4].y = y_offset + (size * 1.732);
            /* Possible weaknesses found:
             *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + 480)' is a pointer; did you mean to use '->'?
             *  member reference base type 'Point[6]' is not a structure or union
             */
            hexGrid[i * cols + j][5].x = x_offset;
            /* Possible weaknesses found:
             *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + 480)' is a pointer; did you mean to use '->'?
             *  member reference base type 'Point[6]' is not a structure or union
             */
            hexGrid[i * cols + j][5].y = y_offset + (size * 0.866);
        }
    }
    return hexGrid;
}

void printHexagonGrid(PointList* hexGrid, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("Hexagon at (%d, %d):\n", i, j);
            for (int k = 0; k < 6; ++k) {
                /* Possible weaknesses found:
                 *  member reference base type 'Point[6]' is not a structure or union
                 *  '(Point *)(*(hexGrid + (sizetype)((long unsigned int)(i * cols + j) * 8)) + (sizetype)((long unsigned int)k * 96))' is a pointer; did you mean to use '->'?
                 */
                printf("  Vertex %d: (%.2f, %.2f)\n", k, hexGrid[i * cols + j][k].x, hexGrid[i * cols + j][k].y);
            }
        }
    }
}

void freeHexagonGrid(PointList* hexGrid, int rows, int cols) {
    for (int i = 0; i < rows * cols; ++i) {
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