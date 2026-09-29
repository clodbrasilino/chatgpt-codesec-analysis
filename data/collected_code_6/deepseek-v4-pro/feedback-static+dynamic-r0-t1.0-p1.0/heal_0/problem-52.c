#include <stdio.h>

double parallelogram_area(double base, double height) {
    if (base < 0 || height < 0) {
        return -1;
    }
    return base * height;
}

int main(void) {
    double base, height, area;
    
    printf("Enter base: ");
    if (scanf("%lf", &base) != 1) {
        return 1;
    }
    
    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        return 1;
    }
    
    area = parallelogram_area(base, height);
    
    if (area < 0) {
        printf("Invalid input: dimensions cannot be negative\n");
        return 1;
    }
    
    printf("Area of parallelogram: %.2f\n", area);
    
    return 0;
}