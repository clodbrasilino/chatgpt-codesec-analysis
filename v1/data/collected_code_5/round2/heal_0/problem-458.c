#include <stdio.h>

double rectangleArea(double length, double width) {
    return length * width;
}

int main() {
    double length, width;

    printf("Enter length of the rectangle: ");
    scanf("%lf", &length);
    if(length <= 0) {
        printf("Length must be a positive number.\n");
        return 1;
    }

    printf("Enter width of the rectangle: ");
    scanf("%lf", &width);
    if(width <= 0) {
        printf("Width must be a positive number.\n");
        return 1;
    }

    double area = rectangleArea(length, width);
    printf("Area of rectangle: %.2lf\n", area);

    return 0;
}