#include <stdio.h>
#include <math.h>
#include <complex.h>

double get_complex_angle(double complex z) {
    return carg(z);
}

int main(void) {
    double complex z1 = 1.0 + 1.0 * I;
    double complex z2 = -1.0 + 0.0 * I;
    
    double angle1 = get_complex_angle(z1);
    double angle2 = get_complex_angle(z2);
    
    printf("%f\n", angle1);
    printf("%f\n", angle2);
    
    return 0;
}