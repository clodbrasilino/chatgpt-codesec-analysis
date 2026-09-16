#include <stdio.h>

double calculate_perimeter(int sides, double length) {
    return sides * length;
}

int main() {
    int sides;
    double length;
    
    printf("Enter the number of sides: ");
    if (scanf("%d", &sides) != 1 || sides <= 0) {
        printf("Invalid input for number of sides.\n");
        return 1;
    }

    printf("Enter the length of each side: ");
    if (scanf("%lf", &length) != 1 || length <= 0.0) {
        printf("Invalid input for length of each side.\n");
        return 1;
    }

    double perimeter = calculate_perimeter(sides, length);
    printf("The perimeter of the polygon is: %.2f\n", perimeter);

    return 0;
}