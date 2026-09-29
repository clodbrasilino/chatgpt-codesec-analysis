#include <stdio.h>
#include <math.h>
#include <complex.h>

double get_angle_of_complex(double complex z) {
    return carg(z);
}

int main() {
    double complex cnum = 3.0 + 4.0 * I;
    double angle = get_angle_of_complex(cnum);
    printf("The angle of the complex number is: %f radians\n", angle);
    return 0;
}