#include <stdio.h>

double rectangle_area(double width, double height) {
    return width * height;
}

int main() {
    double width, height;
    printf("Enter the width of the rectangle: ");
    if (scanf("%lf", &width) != 1) {
        fprintf(stderr, "Invalid input for width.\n");
        return 1;
    }
    printf("Enter the height of the rectangle: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input for height.\n");
        return 1;
    }

    double area = rectangle_area(width, height);
    printf("The area of the rectangle is: %.2f\n", area);

    return 0;
}