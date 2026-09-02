#include <stdio.h>

double calculate_perimeter(double side) {
    return 4.0 * side;
}

int main() {
    double side;
    printf("Enter the length of a side of the rhombus: ");
    if (scanf("%lf", &side) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    double perimeter = calculate_perimeter(side);
    printf("The perimeter of the rhombus is: %.2f\n", perimeter);
    return 0;
}