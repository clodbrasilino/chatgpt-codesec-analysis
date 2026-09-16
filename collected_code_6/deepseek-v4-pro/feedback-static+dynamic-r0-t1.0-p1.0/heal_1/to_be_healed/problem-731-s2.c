#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
 /* Possible weaknesses found:
  *  test case 1 failed: expected 566.3586699569488, got <no output>
  *  test case 2 failed: expected 1521.8090132193388, got <no output>
  *  test case 0 failed: expected 204.20352248333654, got <no output>
  */

double lateral_surface_area_cone(double radius, double height) {
    if (radius < 0 || height < 0) {
        fprintf(stderr, "Error: radius and height must be non-negative.\n");
        exit(EXIT_FAILURE);
    }
    if (radius == 0 || height == 0) {
        return 0.0;
    }
    double slant_height = sqrt(radius * radius + height * height);
    return M_PI * radius * slant_height;
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    
    printf("Enter radius of cone: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter height of cone: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height.\n");
        return EXIT_FAILURE;
    }
    
    double area = lateral_surface_area_cone(radius, height);
    printf("Lateral surface area of cone: %.2f\n", area);
    
    return 0;
}