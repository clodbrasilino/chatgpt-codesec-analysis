#include <stdio.h>

int isValidTriangle(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0)
        return 0;
    if (a + b > c && b + c > a && a + c > b)
        return 1;
    return 0;
}

int main(void) {
    double a, b, c;
    
    printf("Enter three sides of triangle: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (isValidTriangle(a, b, c))
        printf("Valid triangle\n");
    else
        printf("Invalid triangle\n");
    
    return 0;
}