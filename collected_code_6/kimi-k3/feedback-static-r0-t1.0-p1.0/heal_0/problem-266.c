#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>

double calculate_lateral_surface_area(double side_length) {
    if (side_length < 0.0 || isnan(side_length) || isinf(side_length)) {
        errno = EDOM;
        return -1.0;
    }
    
    return 4.0 * side_length * side_length;
}

int main(void) {
    double side_length = 0.0;
    double result = 0.0;
    
    printf("Enter the side length of the cube: ");
    
    if (scanf("%lf", &side_length) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    result = calculate_lateral_surface_area(side_length);
    
    if (errno == EDOM) {
        fprintf(stderr, "Error: Side length must be a non-negative finite number\n");
        return EXIT_FAILURE;
    }
    
    printf("Lateral surface area: %.2f\n", result);
    
    return EXIT_SUCCESS;
}