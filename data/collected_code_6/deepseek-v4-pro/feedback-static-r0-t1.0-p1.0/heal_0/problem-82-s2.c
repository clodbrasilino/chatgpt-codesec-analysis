#include <stdio.h>
#include <math.h>

double sphere_volume(double radius) {
    return (4.0 / 3.0) * M_PI * pow(radius, 3);
}

int main(void) {
    double radius;
    
    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (radius < 0) {
        fprintf(stderr, "Radius cannot be negative\n");
        return 1;
    }
    
    printf("Volume: %.2f\n", sphere_volume(radius));
    
    return 0;
}