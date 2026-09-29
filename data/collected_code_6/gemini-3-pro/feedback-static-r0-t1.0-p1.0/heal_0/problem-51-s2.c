#include <stdio.h>
#include <stdlib.h>

int isEquilateral(double side1, double side2, double side3) {
    if (side1 <= 0.0 || side2 <= 0.0 || side3 <= 0.0) {
        return 0;
    }
    if (side1 == side2 && side2 == side3) {
        return 1;
    }
    return 0;
}

int main(void) {
    double s1, s2, s3;
    
    if (scanf("%lf %lf %lf", &s1, &s2, &s3) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (isEquilateral(s1, s2, s3)) {
        printf("The triangle is equilateral.\n");
    } else {
        printf("The triangle is not equilateral.\n");
    }
    
    return EXIT_SUCCESS;
}