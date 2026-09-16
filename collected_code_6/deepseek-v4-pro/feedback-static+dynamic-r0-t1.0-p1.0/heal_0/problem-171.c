#include <stdio.h>
#include <math.h>

double calculate_pentagon_perimeter(double side_length) {
    return 5.0 * side_length;
}

int main(void) {
    double side = 0.0;
    
    printf("Enter the side length of the pentagon: ");
    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    if (side <= 0.0) {
        fprintf(stderr, "Error: Side length must be positive\n");
        return 1;
    }
    
    double perimeter = calculate_pentagon_perimeter(side);
    printf("Perimeter of the pentagon: %.2f\n", perimeter);
    
    return 0;
}