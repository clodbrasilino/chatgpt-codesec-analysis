#include <stdio.h>
#include <complex.h>
#include <math.h>

double get_complex_number_angle(double complex cn){
    double real_part = creal(cn);
    double imag_part = cimag(cn);

    if(real_part == 0 && imag_part == 0){
        printf("Exception: Zero complex number does not have an angle.\n");
        return 0.0;
    }

    double angle = atan2(imag_part, real_part);
    return angle;
}

int main(){
    double complex number = 3 + 2*I;
    
    double angle = get_complex_number_angle(number);
    printf("The angle of the complex number is: %f\n", angle);

    return 0;
}