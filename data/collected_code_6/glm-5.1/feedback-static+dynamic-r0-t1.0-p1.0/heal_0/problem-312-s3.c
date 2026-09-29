#include <stdio.h>
#include <math.h>

double calculate_cone_volume(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return NAN;
    }
    if (radius == 0.0 || height == 0.0) {
        return 0.0;
    }
    return (1.0 / 3.0) * M_PI * pow(radius, 2.0) * height;
}

int main(void) {
    double r = 5.0;
    double h = 10.0;
    
    double volume = calculate_cone_volume(r, h);
    
    if (isnan(volume)) {
        return 1;
    }
    
    printf("%f\n", volume);
    return 0;
}