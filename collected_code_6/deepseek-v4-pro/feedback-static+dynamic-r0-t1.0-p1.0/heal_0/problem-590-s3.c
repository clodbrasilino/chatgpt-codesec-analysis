#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double magnitude;
    double angle_rad;
} PolarCoordinate;

typedef struct {
    double x;
    double y;
} RectangularCoordinate;

RectangularCoordinate polar_to_rectangular(const PolarCoordinate *polar) {
    RectangularCoordinate rect;
    rect.x = polar->magnitude * cos(polar->angle_rad);
    rect.y = polar->magnitude * sin(polar->angle_rad);
    return rect;
}

int main(void) {
    PolarCoordinate polar = {5.0, PI / 4.0};
    RectangularCoordinate rect = polar_to_rectangular(&polar);
    
    printf("Polar: (%.2f, %.2f rad)\n", polar.magnitude, polar.angle_rad);
    printf("Rectangular: (%.2f, %.2f)\n", rect.x, rect.y);
    
    return 0;
}