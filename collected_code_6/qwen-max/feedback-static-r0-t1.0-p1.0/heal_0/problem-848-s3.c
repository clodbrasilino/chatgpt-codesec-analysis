#include <stdio.h>

double trapezium_area(double a, double b, double h) {
    return 0.5 * (a + b) * h;
}

int main() {
    double base1, base2, height;
    printf("Enter the length of the first base: ");
    if(scanf("%lf", &base1) != 1) return 1;
    printf("Enter the length of the second base: ");
    if(scanf("%lf", &base2) != 1) return 1;
    printf("Enter the height: ");
    if(scanf("%lf", &height) != 1) return 1;
    
    double area = trapezium_area(base1, base2, height);
    printf("The area of the trapezium is: %.2f\n", area);
    return 0;
}