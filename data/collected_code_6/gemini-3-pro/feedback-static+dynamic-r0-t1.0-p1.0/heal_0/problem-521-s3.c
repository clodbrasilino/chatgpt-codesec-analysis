#include <stdio.h>
#include <stdbool.h>

bool is_scalene(double side1, double side2, double side3) {
    if (side1 <= 0 || side2 <= 0 || side3 <= 0 ||
        side1 + side2 <= side3 || 
        side1 + side3 <= side2 || 
        side2 + side3 <= side1) {
        return false;
    }
    
    return (side1 != side2 && side1 != side3 && side2 != side3);
}

int main() {
    double s1, s2, s3;
    
    if (scanf("%lf %lf %lf", &s1, &s2, &s3) != 3) {
        return 1;
    }
    
    if (is_scalene(s1, s2, s3)) {
        printf("The triangle is scalene.\n");
    } else {
        printf("The triangle is not scalene.\n");
    }
    
    return 0;
}