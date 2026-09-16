#include <stdio.h>
#include <stdlib.h>

double calculate_triangle_perimeter(double a, double b, double c) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return -1.0;
    }
    if ((a + b <= c) || (a + c <= b) || (b + c <= a)) {
        return -1.0;
    }
    return a + b + c;
}

int main(void) {
    double a = 3.0;
    double b = 4.0;
    double c = 5.0;
    
    double perimeter = calculate_triangle_perimeter(a, b, c);
    
    if (perimeter < 0.0) {
        fprintf(stderr, "Error: Invalid triangle sides.\n");
        return EXIT_FAILURE;
    }
    
    printf("The perimeter of the triangle is: %.2f\n", perimeter);
    
    return EXIT_SUCCESS;
}