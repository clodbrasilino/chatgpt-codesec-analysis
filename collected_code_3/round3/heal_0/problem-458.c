#include <stdio.h>

float areaOfRectangle(float length, float width) {
    return length * width;
}

int main() {
    float length, width, area;

    printf("Enter length of the rectangle: ");
    scanf("%f", &length);

    printf("Enter width of the rectangle: ");
    scanf("%f", &width);

    area = areaOfRectangle(length, width);

    printf("Area of the rectangle: %.2f\n", area);

    return 0;
}