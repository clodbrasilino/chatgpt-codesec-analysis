#include <stdio.h>
#include <float.h>
#include <math.h>

double calculate_rectangle_area(double length, double width) {
    if (length < 0.0 || width < 0.0 || isnan(length) || isnan(width)) {
        return -1.0;
    }
    
    if (length > 0.0 && width > DBL_MAX / length) {
        return -1.0;
    }
    
    return length * width;
}

int main(void) {
    double length, width;
    
    printf("Enter length and width: ");
    
    if (scanf("%lf %lf", &length, &width) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    double area = calculate_rectangle_area(length, width);
    
    if (area < 0.0) {
        fprintf(stderr, "Invalid dimensions or overflow\n");
        return 1;
    }
    
    printf("Area: %.2f\n", area);
    
    return 0;
}