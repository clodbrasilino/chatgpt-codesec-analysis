#include <stdio.h>

double calculate_lateral_surface_area(double length, double width, double height) {
    if (length < 0.0 || width < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * height * (length + width);
}

int main(void) {
    double length, width, height;
    double result;
    
    if (scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        return 1;
    }
    
    result = calculate_lateral_surface_area(length, width, height);
    
    if (result < 0.0) {
        return 1;
    }
    
    printf("%.2f\n", result);
    
    return 0;
}