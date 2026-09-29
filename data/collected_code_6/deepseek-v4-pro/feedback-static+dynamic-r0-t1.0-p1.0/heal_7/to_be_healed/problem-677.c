#include <stdio.h>
#include <stdbool.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

bool is_valid_triangle(float a, float b, float c) {
    if (isnan(a) || isnan(b) || isnan(c) || isinf(a) || isinf(b) || isinf(c)) {
        return false;
    }
    if (a <= 0.0f || b <= 0.0f || c <= 0.0f) {
        return false;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return false;
    }
    return true;
}

int main(void) {
    float side1, side2, side3;
    
    printf("Enter three side lengths: ");
    if (scanf("%f %f %f", &side1, &side2, &side3) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_valid_triangle(side1, side2, side3)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}