#include <stdio.h>

double perimeter_of_square(double side) {
    return 4.0 * side;
}

int main() {
    double side = 5.0;
    double perimeter = perimeter_of_square(side);
    printf("Perimeter of the square: %.2f\n", perimeter);
    return 0;
}