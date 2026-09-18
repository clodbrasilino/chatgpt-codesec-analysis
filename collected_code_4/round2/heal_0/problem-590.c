#include <stdio.h>
#include <math.h>

struct polar {
    double r;
    double theta;
};

struct rectangular {
    double x;
    double y;
};

struct rectangular polarToRectangular(struct polar p) {
    struct rectangular r;
    r.x = p.r * cos(p.theta);
    r.y = p.r * sin(p.theta);
    return r;
}

int main() {
    struct polar p;
    printf("Enter radius: ");
    scanf("%lf", &p.r);
    printf("Enter angle in radians: ");
    scanf("%lf", &p.theta);

    struct rectangular r = polarToRectangular(p);
    printf("Rectangular coordinates are: (%f, %f)\n", r.x, r.y);

    return 0;
}