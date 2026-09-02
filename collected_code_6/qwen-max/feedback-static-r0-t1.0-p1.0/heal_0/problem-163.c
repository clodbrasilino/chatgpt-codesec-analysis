#include <stdio.h>
#include <math.h>

double calculatePolygonArea(int sides, double side_length) {
    return (0.25 * sides * pow(side_length, 2)) / tan(M_PI / sides);
}

int main() {
    int sides;
    double side_length;

    printf("Enter the number of sides: ");
    if (scanf("%d", &sides) != 1 || sides < 3) {
        printf("Error: Invalid input for number of sides.\n");
        return 1;
    }

    printf("Enter the length of a side: ");
    if (scanf("%lf", &side_length) != 1 || side_length <= 0) {
        printf("Error: Invalid input for side length.\n");
        return 1;
    }

    double area = calculatePolygonArea(sides, side_length);
    printf("The area of the regular polygon is: %.2f\n", area);

    return 0;
}