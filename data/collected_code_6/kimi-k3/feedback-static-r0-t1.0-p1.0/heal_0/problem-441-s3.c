#include <stdio.h>
#include <math.h>

double calculate_surface_area(double side_length) {
    if (side_length < 0.0) {
        return -1.0;
    }
    return 6.0 * side_length * side_length;
}

int main(void) {
    double side_length = 0.0;
    double surface_area = 0.0;
    
    printf("Enter the side length of the cube: ");
    
    if (scanf("%lf", &side_length) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    surface_area = calculate_surface_area(side_length);
    
    if (surface_area < 0.0) {
        fprintf(stderr, "Invalid side length\n");
        return 1;
    }
    
    printf("Surface area: %.2f\n", surface_area);
    
    return 0;
}