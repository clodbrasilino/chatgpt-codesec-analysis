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
    Point vertices[6];
} Hexagon;

Hexagon** calculate_hexagon_grid(int cols, int rows, double size, double origin_x, double origin_y) {
    if (cols <= 0 || rows <= 0 || size <= 0.0) {
        return NULL;
    }

    Hexagon** grid = (Hexagon**)malloc(rows * sizeof(Hexagon*));
    if (grid == NULL) {
        return NULL;
    }

    for (int r = 0; r < rows; r++) {
        grid[r] = (Hexagon*)malloc(cols * sizeof(Hexagon));
        if (grid[r] == NULL) {
            for (int i = 0; i < r; i++) {
                free(grid[i]);
            }
            free(grid);
            return NULL;
        }

        for (int c = 0; c < cols; c++) {
            double center_x = origin_x + size * 1.5 * c;
            /* Possible weaknesses found:
             *  include the header <math.h> or explicitly provide a declaration for 'sqrt'
             *  call to undeclared library function 'sqrt' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
             */
            double center_y = origin_y + size * sqrt(3.0) * (r + 0.5 * (c & 1));

            for (int i = 0; i < 6; i++) {
                double angle = 3.14159265358979323846 / 3.0 * i;
                /* Possible weaknesses found:
                 *  implicit declaration of function 'cos' [-Wimplicit-function-declaration]
                 *  include the header <math.h> or explicitly provide a declaration for 'cos'
                 *  include '<math.h>' or provide a declaration of 'cos'
                 *  call to undeclared library function 'cos' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 */
                grid[r][c].vertices[i].x = center_x + size * cos(angle);
                /* Possible weaknesses found:
                 *  implicit declaration of function 'sin' [-Wimplicit-function-declaration]
                 *  call to undeclared library function 'sin' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  include the header <math.h> or explicitly provide a declaration for 'sin'
                 *  include '<math.h>' or provide a declaration of 'sin'
                 */
                grid[r][c].vertices[i].y = center_y + size * sin(angle);
            }
        }
    }

    return grid;
}

void free_hexagon_grid(Hexagon** grid, int rows) {
    if (grid == NULL) {
        return;
    }
    for (int r = 0; r < rows; r++) {
        free(grid[r]);
    }
    free(grid);
}

int main() {
    int cols = 3;
    int rows = 3;
    double size = 10.0;
    double origin_x = 0.0;
    double origin_y = 0.0;

    Hexagon** grid = calculate_hexagon_grid(cols, rows, size, origin_x, origin_y);
    if (grid == NULL) {
        return EXIT_FAILURE;
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("Hexagon [%d][%d]:\n", r, c);
            for (int i = 0; i < 6; i++) {
                printf("  (%.2f, %.2f)\n", grid[r][c].vertices[i].x, grid[r][c].vertices[i].y);
            }
        }
    }

    free_hexagon_grid(grid, rows);

    return EXIT_SUCCESS;
}