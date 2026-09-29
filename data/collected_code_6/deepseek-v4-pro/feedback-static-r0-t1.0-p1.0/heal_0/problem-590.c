#include <stdio.h>
#include <math.h>

typedef struct {
    double r;
    double theta;
} PolarCoord;

typedef struct {
    double x;
    double y;
} RectCoord;

RectCoord polar_to_rect(PolarCoord polar) {
    RectCoord rect;
    rect.x = polar.r * cos(polar.theta);
    rect.y = polar.r * sin(polar.theta);
    return rect;
}

int main(void) {
    PolarCoord polar;
    RectCoord rect;
    
    printf("Enter polar coordinates (r theta in radians): ");
    if (scanf("%lf %lf", &polar.r, &polar.theta) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    rect = polar_to_rect(polar);
    
    printf("Rectangular coordinates: (%.6f, %.6f)\n", rect.x, rect.y);
    
    return 0;
}