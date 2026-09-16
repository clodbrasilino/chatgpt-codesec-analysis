#include <stdio.h>
#include <math.h>

double calculate_rhombus_perimeter(double side_length) {
    if (side_length <= 0.0 || !isfinite(side_length)) {
        return -1.0;
    }
    return 4.0 * side_length;
}

int main(void) {
    double side_length = 0.0;
    double perimeter = 0.0;

    printf("Enter the side length of the rhombus: ");
    
    if (scanf("%lf", &side_length) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    perimeter = calculate_rhombus_perimeter(side_length);
    
    if (perimeter < 0.0) {
        fprintf(stderr, "Invalid side length\n");
        return 1;
    }

    printf("Perimeter of the rhombus: %.2f\n", perimeter);
    
    return 0;
}