#include <stdio.h>
#include <stdlib.h>

double triangular_prism_volume(double base_area, double height) {
    if (base_area < 0.0 || height < 0.0) {
        return -1.0;
    }
    return base_area * height;
}

int main(void) {
    double base_area = 0.0;
    double prism_height = 0.0;
    
    if (scanf("%lf %lf", &base_area, &prism_height) != 2) {
        return EXIT_FAILURE;
    }
    
    double volume = triangular_prism_volume(base_area, prism_height);
    
    if (volume < 0.0) {
        return EXIT_FAILURE;
    }
    
    printf("%f\n", volume);
    
    return EXIT_SUCCESS;
}