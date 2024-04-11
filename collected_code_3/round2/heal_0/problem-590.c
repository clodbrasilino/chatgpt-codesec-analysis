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
    Rectangular rectangular;
    rectangular.x = polar.r * cos(polar.theta);
    rectangular.y = polar.r * sin(polar.theta);
    return rectangular;
}

int main() {
    Polar polar;
    printf("Enter radius: ");
    scanf("%lf", &polar.r);
    printf("Enter angle in radians: ");
    scanf("%lf", &polar.theta);

    Rectangular rectangular = polarToRectangular(polar);

    printf("Rectangular coordinates are: x = %.2lf, y = %.2lf\n", rectangular.x, rectangular.y);

    return 0;
}