#include <stdio.h>
#include <math.h>

double sphere_volume(double radius) {
    if (radius < 0.0) {
        return NAN;
    }
    return (4.0 / 3.0) * M_PI * pow(radius, 3);
}

int main(int argc, char *argv[]) {
    double r = 5.0;
    double vol = sphere_volume(r);
    if (isnan(vol)) {
        return 1;
    }
    printf("%f\n", vol);
    return 0;
}