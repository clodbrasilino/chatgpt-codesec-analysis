#include <stdio.h>

double calculate_perimeter(int sides, double length);

int main() {
    int sides;
    double length;
    printf("Enter the number of sides: ");
    scanf("%d", &sides);
    printf("Enter the length of each side: ");
    scanf("%lf", &length);

    if (sides <= 0 || length <= 0) {
        fprintf(stderr, "Invalid input. Sides and length must be greater than 0.\n");
        return 1;
    }

    double perimeter = calculate_perimeter(sides, length);
    printf("The perimeter of the polygon is: %.2f\n", perimeter);
    return 0;
}

double calculate_perimeter(int sides, double length) {
    return (double)sides * length;
}