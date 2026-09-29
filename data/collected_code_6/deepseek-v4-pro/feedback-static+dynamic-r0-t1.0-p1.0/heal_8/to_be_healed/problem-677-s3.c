#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected False, got 1
  */

bool is_valid_triangle(float a, float b, float c) {
    if (a <= 0.0f || b <= 0.0f || c <= 0.0f) {
        return false;
    }
    
    if (isinf(a) || isinf(b) || isinf(c)) {
        return false;
    }
    
    if (isnan(a) || isnan(b) || isnan(c)) {
        return false;
    }
    
    if (a > FLT_MAX - b || b > FLT_MAX - c || a > FLT_MAX - c) {
        return false;
    }
    
    if (a + b <= c || b + c <= a || a + c <= b) {
        return false;
    }
    
    return true;
}

int main(void) {
    float side1, side2, side3;
    
    printf("Enter three sides of a triangle: ");
    if (scanf("%f %f %f", &side1, &side2, &side3) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_valid_triangle(side1, side2, side3)) {
        printf("Valid triangle\n");
    } else {
        printf("Invalid triangle\n");
    }
    
    return 0;
}