#include <stdio.h>

float findPerimeter(float a, float b, float c) {
    return a + b + c;
}

int main() {
    float a, b, c;
    printf("Enter the lengths of the three sides of the triangle: ");
    scanf("%f %f %f", &a, &b, &c);
    printf("The perimeter of the triangle is: %.2f\n", findPerimeter(a, b, c));
    return 0;
}