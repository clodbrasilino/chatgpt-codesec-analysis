#include <stdio.h>
#include <math.h>

double calculate_discriminant(double a, double b, double c) {
    return b * b - 4 * a * c;
}

int main() {
    double a, b, c, discriminant;
    
    printf("Enter coefficients a, b and c: ");
    if(scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if(a == 0) {
        printf("The value of a should not be zero\n");
        return 1;
    }
    
    discriminant = calculate_discriminant(a, b, c);
    
    if(discriminant < 0) {
        printf("Discriminant is negative, the equation has no real roots\n");
    }
    else if(discriminant == 0) {
        printf("Discriminant is zero, the equation has one real root\n");
    }
    else {
        printf("Discriminant is positive, the equation has two real roots\n");
    }
    
    return 0;
}