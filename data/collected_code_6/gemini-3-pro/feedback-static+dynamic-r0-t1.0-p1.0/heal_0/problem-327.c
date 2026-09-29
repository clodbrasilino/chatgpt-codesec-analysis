#include <stdio.h>
#include <stdbool.h>

bool is_isosceles(double side1, double side2, double side3) {
    if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
        return false;
    }
    
    if ((side1 + side2 <= side3) || (side1 + side3 <= side2) || (side2 + side3 <= side1)) {
        return false;
    }
    
    if (side1 == side2 || side1 == side3 || side2 == side3) {
        return true;
    }
    
    return false;
}

int main(void) {
    double s1 = 0.0;
    double s2 = 0.0;
    double s3 = 0.0;
    int result = 0;
    
    result = scanf("%lf %lf %lf", &s1, &s2, &s3);
    
    if (result != 3) {
        return 1;
    }
    
    if (is_isosceles(s1, s2, s3)) {
        printf("The triangle is isosceles.\n");
    } else {
        printf("The triangle is not isosceles.\n");
    }
    
    return 0;
}