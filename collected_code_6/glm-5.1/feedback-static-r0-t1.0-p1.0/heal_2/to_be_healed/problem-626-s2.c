#include <stdio.h>
#include <stdlib.h>

double find_largest_triangle_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return radius * radius;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    double radius = strtod(argv[1], &endptr);
    
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    
    double area = find_largest_triangle_area(radius);
    
    if (area < 0.0) {
        return EXIT_FAILURE;
    }
    
    printf("%.6f\n", area);
    
    return EXIT_SUCCESS;
}