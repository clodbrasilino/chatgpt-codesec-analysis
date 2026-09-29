#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double radius;
    double angle;
} PolarCoordinate;

typedef struct {
    double x;
    double y;
} RectangularCoordinate;

RectangularCoordinate convert_polar_to_rectangular(const PolarCoordinate polar) {
    RectangularCoordinate rect;
    rect.x = polar.radius * cos(polar.angle);
    rect.y = polar.radius * sin(polar.angle);
    return rect;
}

int main(void) {
    PolarCoordinate polar;
    
    if (scanf("%lf %lf", &polar.radius, &polar.angle) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    RectangularCoordinate rect = convert_polar_to_rectangular(polar);
    
    printf("%f %f\n", rect.x, rect.y);
    
    return EXIT_SUCCESS;
}