#include <stdio.h>

#define PI 3.14159

double circumference(double radius) {
    return 2 * PI * radius;
}

int main() {
    double radius = 0;
    printf("Enter the radius: ");
    if(scanf("%lf", &radius) != 1) {
        printf("Invalid input! Please enter a number.\n");
        return -1;
    }

    if(radius < 0) {
        printf("Invalid input! Radius cannot be negative.\n");
        return -1;
    }

    double result = circumference(radius);
    printf("The circumference of the circle is: %.2f\n", result);

    return 0;
}