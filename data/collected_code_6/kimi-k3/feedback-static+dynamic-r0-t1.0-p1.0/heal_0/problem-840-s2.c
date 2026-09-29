#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

bool roots_equal_opposite(double a, double b, double c, bool *result)
{
    if (result == NULL) {
        return false;
    }
    
    if (fabs(a) < DBL_EPSILON) {
        return false;
    }
    
    double discriminant = b * b - 4.0 * a * c;
    
    if (discriminant < 0.0) {
        return false;
    }
    
    *result = (fabs(b) < DBL_EPSILON);
    return true;
}

int main(void)
{
    double a, b, c;
    bool result;
    
    printf("Enter coefficients a, b, c: ");
    
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (!roots_equal_opposite(a, b, c, &result)) {
        fprintf(stderr, "Error: Not a valid quadratic equation or no real roots\n");
        return 1;
    }
    
    if (result) {
        printf("Roots are numerically equal but opposite in sign\n");
    } else {
        printf("Roots are not numerically equal but opposite in sign\n");
    }
    
    return 0;
}