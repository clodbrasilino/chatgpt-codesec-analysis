#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double circle_area(double radius) {
    if (radius < 0.0) {
        fprintf(stderr, "Error: Radius cannot be negative\n");
        exit(EXIT_FAILURE);
    }
    return PI * radius * radius;
}

int main(void) {
    double radius = 5.0;
    /* Possible weaknesses found:
     *  'surface_type' is assigned value '0' here.
     */
    int surface_type = 0;
    
    /* Possible weaknesses found:
     *  The comparison 'surface_type != 0' is always false.
     *  The comparison 'surface_type != 0' is always false. [knownConditionTrueFalse]
     */
    if (surface_type != 0 && surface_type != 1) {
        fprintf(stderr, "Error: surface_type must be 0 (top) or 1 (bottom)\n");
        return EXIT_FAILURE;
    }
    
    double area = circle_area(radius);
    printf("The %s surface area of the cylinder is: %.2f\n", 
           /* Possible weaknesses found:
            *  The comparison 'surface_type == 0' is always true. [knownConditionTrueFalse]
            *  The comparison 'surface_type == 0' is always true.
            */
           surface_type == 0 ? "top" : "bottom", area);
    
    return 0;
}