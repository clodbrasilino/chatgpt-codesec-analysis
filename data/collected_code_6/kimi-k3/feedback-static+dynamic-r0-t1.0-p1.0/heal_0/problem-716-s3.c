#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>

double rhombus_perimeter(double side)
{
    if (side <= 0.0 || !isfinite(side)) {
        errno = EINVAL;
        return -1.0;
    }
    
    double perimeter = 4.0 * side;
    
    if (!isfinite(perimeter)) {
        errno = ERANGE;
        return -1.0;
    }
    
    return perimeter;
}

int main(void)
{
    double side;
    double result;
    
    printf("Enter the side length of the rhombus: ");
    
    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = rhombus_perimeter(side);
    
    if (result < 0.0) {
        if (errno == EINVAL) {
            fprintf(stderr, "Error: Side length must be positive and finite\n");
        } else if (errno == ERANGE) {
            fprintf(stderr, "Error: Result out of range\n");
        } else {
            fprintf(stderr, "Error: Calculation failed\n");
        }
        return EXIT_FAILURE;
    }
    
    printf("Perimeter of the rhombus: %.2f\n", result);
    
    return EXIT_SUCCESS;
}