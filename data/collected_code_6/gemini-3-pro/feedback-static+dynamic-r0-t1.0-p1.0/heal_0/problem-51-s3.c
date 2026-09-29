#include <stdio.h>
#include <stdbool.h>

bool isEquilateral(double side1, double side2, double side3) {
    if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
        return false;
    }
    
    if ((side1 + side2 <= side3) || (side1 + side3 <= side2) || (side2 + side3 <= side1)) {
        return false;
    }

    if (side1 == side2 && side2 == side3) {
        return true;
    }
    
    return false;
}

int main(void) {
    double s1 = 0.0;
    double s2 = 0.0;
    double s3 = 0.0;
    
    int result = scanf("%lf %lf %lf", &s1, &s2, &s3);
    
    if (result != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    if (isEquilateral(s1, s2, s3)) {
        printf("The triangle is equilateral.\n");
    } else {
        printf("The triangle is not equilateral.\n");
    }

    return 0;
}