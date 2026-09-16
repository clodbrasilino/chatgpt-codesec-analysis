#include <stdio.h>
#include <math.h>

double cylinder_volume(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius * height;
}

int main(void) {
    double radius, height, volume;
    
    printf("Enter radius and height: ");
    if (scanf("%lf %lf", &radius, &height) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    volume = cylinder_volume(radius, height);
    if (volume < 0.0) {
        fprintf(stderr, "Invalid dimensions: radius and height must be non-negative\n");
        return 1;
    }
    
    printf("Volume: %.2f\n", volume);
    return 0;
}