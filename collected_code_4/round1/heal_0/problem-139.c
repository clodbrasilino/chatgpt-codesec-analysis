#include <stdio.h>

#define PI 3.14159

double calculate_circumference(double radius) {
    return 2 * PI * radius;
}

int main() {
    double radius, circumference;

    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);

    if(radius <= 0) {
        printf("Invalid input! Radius should be a positive number.");
        return -1;
    }
    
    circumference = calculate_circumference(radius);
    
    printf("Circumference of the circle: %.2lf", circumference);
    
    return 0;
}