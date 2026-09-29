#include <stdio.h>

double calculateTrapeziumArea(double base1, double base2, double height) {
    return 0.5 * (base1 + base2) * height;
}

int main() {
    double base1, base2, height, area;
    
    if (scanf("%lf %lf %lf", &base1, &base2, &height) == 3) {
        area = calculateTrapeziumArea(base1, base2, height);
        printf("The area of the trapezium is: %f\n", area);
    } else {
        printf("Invalid input.\n");
    }
    
    return 0;
}