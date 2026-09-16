#include <stdio.h>
#include <math.h>

double calculate_sphere_volume(double radius) {
    return (4.0 / 3.0) * M_PI * pow(radius, 3);
}

int main(void) {
    double radius;
    
    if (scanf("%lf", &radius) != 1) {
        return 1;
    }
    
    if (radius < 0.0) {
        return 1;
    }
    
    double volume = calculate_sphere_volume(radius);
    
    printf("%f\n", volume);
    
    return 0;
}