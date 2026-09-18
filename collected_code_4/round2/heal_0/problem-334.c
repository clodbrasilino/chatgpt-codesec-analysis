#include <stdio.h>
#include <stdlib.h>

int isTriangleValid(double a, double b, double c) {
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return 1;
    }
    return 0;
}

int main(void) {

    double a, b, c;

    printf("Enter the sides of the triangle:\n");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (isTriangleValid(a, b, c)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }

    return 0;
}