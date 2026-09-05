#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>

double calculate_perimeter(double base, double side) {
    if (base < 0.0 || side < 0.0 || !isfinite(base) || !isfinite(side)) {
        return -1.0;
    }
    if (base > DBL_MAX / 2.0 || side > DBL_MAX / 2.0) {
        return -1.0;
    }
    return 2.0 * (base + side);
}

int main(void) {
    char buffer[256];
    double base, side;
    char *endptr;
    
    printf("Enter base: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    base = strtod(buffer, &endptr);
    if (endptr == buffer || errno == ERANGE || !isfinite(base)) {
        fprintf(stderr, "Invalid input for base\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter side: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    side = strtod(buffer, &endptr);
    if (endptr == buffer || errno == ERANGE || !isfinite(side)) {
        fprintf(stderr, "Invalid input for side\n");
        return EXIT_FAILURE;
    }
    
    double perimeter = calculate_perimeter(base, side);
    if (perimeter < 0.0) {
        fprintf(stderr, "Invalid dimensions or overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Perimeter: %f\n", perimeter);
    return EXIT_SUCCESS;
}