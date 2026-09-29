#include <stdio.h>
#include <math.h>

double sphere_volume(double radius) {
    if (radius < 0.0) {
        return 0.0;
    }
    return (4.0 / 3.0) * M_PI * pow(radius, 3);
}

int main(void) {
    double r = 5.0;
    double vol = sphere_volume(r);
    printf("%f\n", vol);
    return 0;
}