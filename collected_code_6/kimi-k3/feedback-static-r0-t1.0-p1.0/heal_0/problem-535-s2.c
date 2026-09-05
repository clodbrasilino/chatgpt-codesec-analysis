#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>

double cylinder_base_area(double radius) {
    if (radius < 0.0 || !isfinite(radius)) {
        errno = EDOM;
        return -1.0;
    }
    
    double result = M_PI * radius * radius;
    
    if (!isfinite(result)) {
        errno = ERANGE;
        return -1.0;
    }
    
    return result;
}

int main(void) {
    double radius;
    
    printf("Enter cylinder radius: ");
    
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    double area = cylinder_base_area(radius);
    
    if (area < 0.0) {
        if (errno == EDOM) {
            fprintf(stderr, "Radius must be non-negative\n");
        } else if (errno == ERANGE) {
            fprintf(stderr, "Result out of range\n");
        }
        return EXIT_FAILURE;
    }
    
    printf("Surface area: %.6f\n", area);
    
    return EXIT_SUCCESS;
}