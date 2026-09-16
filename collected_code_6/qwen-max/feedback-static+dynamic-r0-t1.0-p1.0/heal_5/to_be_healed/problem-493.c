#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef Point* PointList[6];

PointList** calculateHexagonGrid(int rows, int cols, double size) {
    /* Possible weaknesses found:
     *  Variable created here.
     */
    PointList** hexGrid = malloc(rows * cols * sizeof(PointList*));
    /* Possible weaknesses found:
     *  Condition 'hexGrid==NULL' is always false [knownConditionTrueFalse]
     */
    if (hexGrid == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            hexGrid[i * cols + j] = malloc(6 * sizeof(Point));
            if (hexGrid[i * cols + j] == NULL) {
                for (int k = 0; k < i * cols + j; ++k) {
                    free(hexGrid[k]);
                }
                /* Possible weaknesses found:
                 *  Deallocation of an auto-variable results in undefined behaviour. [autovarInvalidDeallocation]
                 */
                free(hexGrid);
                return NULL;
            }
            
            double y_offset = i * (size * 1.5) + ((j % 2) ? (size * 0.75) : 0);
            double x_offset = j * size * 1.5;
            
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'x' in something not a structure or union
             */
            hexGrid[i * cols + j][0].x = x_offset;
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'y' in something not a structure or union
             */
            hexGrid[i * cols + j][0].y = y_offset;
            
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'x' in something not a structure or union
             */
            hexGrid[i * cols + j][1].x = x_offset + size * 0.5;
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'y' in something not a structure or union
             */
            hexGrid[i * cols + j][1].y = y_offset - (size * 0.866);
            
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'x' in something not a structure or union
             */
            hexGrid[i * cols + j][2].x = x_offset + size * 1.5;
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'y' in something not a structure or union
             */
            hexGrid[i * cols + j][2].y = y_offset;
            
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'x' in something not a structure or union
             */
            hexGrid[i * cols + j][3].x = x_offset + size * 1.5;
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'y' in something not a structure or union
             */
            hexGrid[i * cols + j][3].y = y_offset + (size * 0.866);
            
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'x' in something not a structure or union
             */
            hexGrid[i * cols + j][4].x = x_offset + size * 0.5;
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'y' in something not a structure or union
             */
            hexGrid[i * cols + j][4].y = y_offset + (size * 1.732);
            
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'x' in something not a structure or union
             */
            hexGrid[i * cols + j][5].x = x_offset;
            /* Possible weaknesses found:
             *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
             *  request for member 'y' in something not a structure or union
             */
            hexGrid[i * cols + j][5].y = y_offset + (size * 0.866);
        }
    }
    /* Possible weaknesses found:
     *  Array decayed to pointer here.
     *  Returning pointer to local variable 'hexGrid' that will be invalid when returning. [returnDanglingLifetime]
     *  Returning pointer to local variable 'hexGrid' that will be invalid when returning.
     */
    return hexGrid;
}

void printHexagonGrid(PointList** hexGrid, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("Hexagon at (%d, %d):\n", i, j);
            for (int k = 0; k < 6; ++k) {
                /* Possible weaknesses found:
                 *  member reference base type 'PointList' (aka 'Point *[6]') is not a structure or union
                 *  request for member 'y' in something not a structure or union
                 *  request for member 'x' in something not a structure or union
                 */
                printf("  Vertex %d: (%.2f, %.2f)\n", k, hexGrid[i * cols + j][k].x, hexGrid[i * cols + j][k].y);
            }
        }
    }
}

void freeHexagonGrid(PointList** hexGrid, int rows, int cols) {
    for (int i = 0; i < rows * cols; ++i) {
        free(hexGrid[i]);
    }
    free(hexGrid);
}

int main() {
    int rows = 2;
    int cols = 3;
    double size = 2.0;
    
    PointList** hexGrid = calculateHexagonGrid(rows, cols, size);
    /* Possible weaknesses found:
     *  Condition 'hexGrid!=NULL' is always true [knownConditionTrueFalse]
     */
    if (hexGrid != NULL) {
        printHexagonGrid(hexGrid, rows, cols);
        freeHexagonGrid(hexGrid, rows, cols);
    } else {
        printf("Memory allocation failed.\n");
    }
    
    return 0;
}