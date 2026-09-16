#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'cos'
  */

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    int size;
    Point *points;
} PointsList;

PointsList* create_hexagon(double center_x, double center_y, double radius) {
    PointsList* hex = (PointsList*)malloc(sizeof(PointsList));
    if (hex == NULL) {
        return NULL;
    }
    hex->size = 6;
    hex->points = (Point*)malloc(hex->size * sizeof(Point));
    if (hex->points == NULL) {
        free(hex);
        return NULL;
    }

    for (int i = 0; i < 6; ++i) {
        double angle_deg = 60 * i - 30;
        /* Possible weaknesses found:
         *  'M_PI' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'M_PI'
         */
        double angle_rad = angle_deg * M_PI / 180.0;
        /* Possible weaknesses found:
         *  include the header <math.h> or explicitly provide a declaration for 'cos'
         *  implicit declaration of function 'cos' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'cos' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        hex->points[i].x = center_x + radius * cos(angle_rad);
        /* Possible weaknesses found:
         *  call to undeclared library function 'sin' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'sin'
         *  include '<math.h>' or provide a declaration of 'sin'
         *  implicit declaration of function 'sin' [-Wimplicit-function-declaration]
         */
        hex->points[i].y = center_y + radius * sin(angle_rad);
    }

    return hex;
}

void print_hexagon(PointsList *hex) {
    for (int i = 0; i < hex->size; ++i) {
        printf("(%.2f, %.2f)\n", hex->points[i].x, hex->points[i].y);
    }
}

void free_points_list(PointsList *list) {
    free(list->points);
    free(list);
}

int main() {
    double center_x = 0.0;
    double center_y = 0.0;
    double radius = 1.0;

    PointsList *hex = create_hexagon(center_x, center_y, radius);
    if (hex != NULL) {
        print_hexagon(hex);
        free_points_list(hex);
    } else {
        fprintf(stderr, "Failed to create hexagon\n");
        return 1;
    }

    return 0;
}