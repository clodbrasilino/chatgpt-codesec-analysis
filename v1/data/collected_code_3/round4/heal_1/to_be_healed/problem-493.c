#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point points[6];
} Hexagon;

Hexagon* calculate_hexagon_grid(int grid_size, double hexagon_size) {
    Hexagon* grid = malloc(grid_size * sizeof(Hexagon));
    double half_size = hexagon_size / 2.0;
    double row_height = hexagon_size * 3 / 2;
    /* Possible weaknesses found:
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     *  include '<math.h>' or provide a declaration of 'sqrt'
     *  incompatible implicit declaration of built-in function 'sqrt' [-Wbuiltin-declaration-mismatch]
     */
    double col_width = hexagon_size * sqrt(3);

    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < 6; j++) {
            double angle_deg = 60 * j - 30;
            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  'M_PI' undeclared (first use in this function)
             */
            double angle_rad = M_PI / 180 * angle_deg;
            /* Possible weaknesses found:
             *  include '<math.h>' or provide a declaration of 'cos'
             *  implicit declaration of function 'cos' [-Wimplicit-function-declaration]
             *  incompatible implicit declaration of built-in function 'cos' [-Wbuiltin-declaration-mismatch]
             */
            grid[i].points[j].x = i * col_width + hexagon_size * cos(angle_rad);
            /* Possible weaknesses found:
             *  implicit declaration of function 'sin' [-Wimplicit-function-declaration]
             *  incompatible implicit declaration of built-in function 'sin' [-Wbuiltin-declaration-mismatch]
             *  include '<math.h>' or provide a declaration of 'sin'
             */
            grid[i].points[j].y = i * row_height + hexagon_size * sin(angle_rad);
        }
    }

    return grid;
}

void print_hexagon_grid(Hexagon* grid, int grid_size) {
    for (int i = 0; i < grid_size; i++) {
        printf("Hexagon %d:\n", i + 1);
        for (int j = 0; j < 6; j++) {
            printf("Point %d: (%f, %f)\n", j + 1, grid[i].points[j].x, grid[i].points[j].y);
        }
    }
}

int main() {
    int grid_size = 5;
    double hexagon_size = 1.0;
    Hexagon* grid = calculate_hexagon_grid(grid_size, hexagon_size);
    print_hexagon_grid(grid, grid_size);
    free(grid);
    return 0;
}