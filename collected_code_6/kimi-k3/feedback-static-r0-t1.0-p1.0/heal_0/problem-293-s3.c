#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool calculate_third_side(double a, double b, double *result, char missing_side)
{
    if (result == NULL) {
        return false;
    }
    
    if (a <= 0.0 || b <= 0.0) {
        return false;
    }
    
    switch (missing_side) {
        case 'c':
            *result = sqrt(a * a + b * b);
            return true;
        case 'a':
        case 'b':
            if (b <= a) {
                return false;
            }
            *result = sqrt(b * b - a * a);
            return true;
        default:
            return false;
    }
}

int main(void)
{
    double side1, side2, result;
    char missing;
    int scan_result;
    
    printf("Enter the two known sides: ");
    scan_result = scanf("%lf %lf", &side1, &side2);
    
    if (scan_result != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter missing side (a, b, or c for hypotenuse): ");
    scan_result = scanf(" %c", &missing);
    
    if (scan_result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (!calculate_third_side(side1, side2, &result, missing)) {
        fprintf(stderr, "Invalid parameters\n");
        return 1;
    }
    
    printf("Third side: %.2f\n", result);
    
    return 0;
}