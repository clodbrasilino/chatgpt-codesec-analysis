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

Rectangular polarToRectangular(Polar p) {
    Rectangular r;
    r.x = p.r * cos(p.theta);
    r.y = p.r * sin(p.theta);
    return r;
}

int main() {
    Polar p;
    Rectangular r;

    printf("Enter radius and angle (in radians): ");
    scanf("%lf %lf", &p.r, &p.theta);

    r = polarToRectangular(p);

    printf("Rectangular coordinates are: x = %.2lf, y = %.2lf\n", r.x, r.y);

    return 0;
}