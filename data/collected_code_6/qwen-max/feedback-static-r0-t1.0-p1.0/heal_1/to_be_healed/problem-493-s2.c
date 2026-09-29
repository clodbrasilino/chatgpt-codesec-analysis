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
    Point* points;
    int size;
} PointsList;

void free_points_list(PointsList plist) {
    if (plist.points) {
        free(plist.points);
    }
}

PointsList calculate_hexagon(double cx, double cy, double radius) {
    PointsList plist;
    plist.points = (Point*) malloc(6 * sizeof(Point));
    if (plist.points == NULL) {
        exit(EXIT_FAILURE);
    }
    plist.size = 6;

    for (int i = 0; i < 6; ++i) {
        double angle_deg = 60 * i - 30;
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'M_PI'
         *  'M_PI' undeclared (first use in this function)
         */
        double angle_rad = M_PI / 180 * angle_deg;
        /* Possible weaknesses found:
         *  include the header <math.h> or explicitly provide a declaration for 'cos'
         *  implicit declaration of function 'cos' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'cos' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        plist.points[i].x = cx + radius * cos(angle_rad);
        /* Possible weaknesses found:
         *  implicit declaration of function 'sin' [-Wimplicit-function-declaration]
         *  include '<math.h>' or provide a declaration of 'sin'
         *  include the header <math.h> or explicitly provide a declaration for 'sin'
         *  call to undeclared library function 'sin' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        plist.points[i].y = cy + radius * sin(angle_rad);
    }

    return plist;
}

int main() {
    double center_x = 0.0;
    double center_y = 0.0;
    double radius = 10.0;

    PointsList hexagon = calculate_hexagon(center_x, center_y, radius);

    for (int i = 0; i < hexagon.size; ++i) {
        printf("Point %d: (%.2f, %.2f)\n", i+1, hexagon.points[i].x, hexagon.points[i].y);
    }

    free_points_list(hexagon);

    return 0;
}