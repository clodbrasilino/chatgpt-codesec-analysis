#include <stdio.h>

double calculate_pentagon_perimeter(double side) {
    return 5 * side;
}

int main() {
    double side = 4.0;
    double perimeter = calculate_pentagon_perimeter(side);
    printf("The perimeter of the pentagon is: %f\n", perimeter);
    return 0;
}