#include <stdio.h>

double calculate_perimeter(int sides, double length) {
    if (sides <= 0 || length <= 0) {
        return -1.0;
    }
    return (double)sides * length;
}

int main() {
    int sides = 5;
    double side_length = 3.5;

    double perimeter = calculate_perimeter(sides, side_length);
    if (perimeter >= 0) {
        printf("Perimeter: %.2f\n", perimeter);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}