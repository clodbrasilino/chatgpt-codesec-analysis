#include <stdio.h>
#include <math.h>

typedef struct {
    double r;
    double theta;
} Polar;

typedef struct {
    double x;
    double y;
} Rectangular;

Rectangular polarToRectangular(Polar polar) {
    Rectangular rect;
    rect.x = polar.r * cos(polar.theta);
    rect.y = polar.r * sin(polar.theta);
    return rect;
}

int main() {
    Polar polar;
    Rectangular rect;

    printf("Enter radius and angle (in radians): ");
    scanf("%lf %lf", &polar.r, &polar.theta);

    rect = polarToRectangular(polar);

    printf("Rectangular coordinates are: %.2lf, %.2lf\n", rect.x, rect.y);

    return 0;
}