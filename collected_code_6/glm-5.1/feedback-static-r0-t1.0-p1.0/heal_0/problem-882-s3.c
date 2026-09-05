#include <stdio.h>

double calculate_perimeter(double base, double side) {
    double perimeter = 2.0 * (base + side);
    return perimeter;
}

int main(void) {
    double base = 5.0;
    double side = 3.0;
    double perimeter = calculate_perimeter(base, side);
    printf("%f\n", perimeter);
    return 0;
}