#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

#define PI 3.14159265358979323846

typedef struct {
    double x;
    double y;
} Rectangular;

int polar_to_rectangular(double r, double theta, Rectangular *rect)
{
    if (rect == NULL) {
        return -1;
    }
    if (r < 0.0) {
        return -1;
    }
    if (isnan(r) || isnan(theta) || isinf(r) || isinf(theta)) {
        return -1;
    }
    
    rect->x = r * cos(theta);
    rect->y = r * sin(theta);
    
    return 0;
}

int main(void)
{
    double r, theta;
    Rectangular rect;
    int status;
    
    printf("Enter radius (r): ");
    if (scanf("%lf", &r) != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter angle in radians (theta): ");
    if (scanf("%lf", &theta) != 1) {
        fprintf(stderr, "Invalid input for angle\n");
        return EXIT_FAILURE;
    }
    
    status = polar_to_rectangular(r, theta, &rect);
    if (status != 0) {
        fprintf(stderr, "Invalid polar coordinates\n");
        return EXIT_FAILURE;
    }
    
    printf("Rectangular coordinates: x = %.6f, y = %.6f\n", rect.x, rect.y);
    
    return EXIT_SUCCESS;
}