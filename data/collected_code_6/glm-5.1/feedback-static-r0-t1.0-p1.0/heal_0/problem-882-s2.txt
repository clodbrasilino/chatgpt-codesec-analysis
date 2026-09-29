#include <stdio.h>

double calculate_perimeter(double base, double side) {
    if (base <= 0.0 || side <= 0.0) {
        return -1.0;
    }
    return 2.0 * (base + side);
}

int main(void) {
    double base = 5.0;
    double side = 3.0;
    double perimeter = calculate_perimeter(base, side);

    if (perimeter < 0.0) {
        printf("Invalid input values.\n");
        return 1;
    }

    printf("%.2f\n", perimeter);
    return 0;
}