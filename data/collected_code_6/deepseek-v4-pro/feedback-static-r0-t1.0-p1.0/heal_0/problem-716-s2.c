#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double rhombus_perimeter(double side) {
    return 4.0 * side;
}

int main(void) {
    double side;
    
    printf("Enter the side length of the rhombus: ");
    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (side <= 0.0) {
        fprintf(stderr, "Side length must be positive\n");
        return EXIT_FAILURE;
    }
    
    double perimeter = rhombus_perimeter(side);
    printf("Perimeter of the rhombus: %.2f\n", perimeter);
    
    return EXIT_SUCCESS;
}