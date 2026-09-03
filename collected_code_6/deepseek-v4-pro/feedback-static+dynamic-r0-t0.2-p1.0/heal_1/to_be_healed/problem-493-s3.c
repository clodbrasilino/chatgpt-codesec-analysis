#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point points[6];
} Hexagon;

typedef struct {
    Hexagon *hexagons;
    int count;
} HexagonGrid;

HexagonGrid calculate_hexagon_grid(int rows, int cols, double radius) {
    HexagonGrid grid;
    grid.count = rows * cols;
    grid.hexagons = (Hexagon *)malloc(grid.count * sizeof(Hexagon));
    
    if (grid.hexagons == NULL) {
        grid.count = 0;
        return grid;
    }
    
    double horizontal_spacing = radius * sqrt(3.0);
    double vertical_spacing = radius * 1.5;
    
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            double center_x = col * horizontal_spacing;
            double center_y = row * vertical_spacing;
            
            if (col % 2 == 1) {
                center_y += vertical_spacing / 2.0;
            }
            
            int index = row * cols + col;
            
            for (int i = 0; i < 6; i++) {
                double angle = M_PI / 3.0 * i - M_PI / 6.0;
                grid.hexagons[index].points[i].x = center_x + radius * cos(angle);
                grid.hexagons[index].points[i].y = center_y + radius * sin(angle);
            }
        }
    }
    
    return grid;
}

void free_hexagon_grid(HexagonGrid *grid) {
    if (grid->hexagons != NULL) {
        free(grid->hexagons);
        grid->hexagons = NULL;
        grid->count = 0;
    }
}

int main(void) {
    int rows = 3;
    int cols = 4;
    double radius = 1.0;
    
    HexagonGrid grid = calculate_hexagon_grid(rows, cols, radius);
    
    if (grid.hexagons != NULL) {
        for (int i = 0; i < grid.count; i++) {
            for (int j = 0; j < 6; j++) {
                /* Possible weaknesses found:
                 *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
                 *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
                 */
                printf("Hexagon %d, Point %d: (%.2f, %.2f)\n", 
                       i, j, grid.hexagons[i].points[j].x, grid.hexagons[i].points[j].y);
            }
        }
        free_hexagon_grid(&grid);
    }
    
    return 0;
}