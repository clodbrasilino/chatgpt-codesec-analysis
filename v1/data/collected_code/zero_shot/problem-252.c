#include <math.h>

struct Polar {
    double magnitude;
    double angle;
};

struct Polar convertComplexToPolar(double real, double imag) {
    struct Polar polar;

    polar.magnitude = sqrt(real * real + imag * imag);
    polar.angle = atan2(imag, real);

    return polar;
}