#include <stdio.h>

double parallelogram_perimeter(double base, double side) {
    return 2.0 * (base + side);
}

int main(void) {
    double base = 100.0;
    double side = 100.0;
    double perimeter = parallelogram_perimeter(base, side);
    printf("Perimeter: %.2f\n", perimeter);
    
    base = 200.0;
    side = 100.0;
    perimeter = parallelogram_perimeter(base, side);
    printf("Perimeter: %.2f\n", perimeter);
    
    base = 36.0;
    side = 36.0;
    perimeter = parallelogram_perimeter(base, side);
    printf("Perimeter: %.2f\n", perimeter);
    
    return 0;
}