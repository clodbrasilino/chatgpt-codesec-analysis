#include <stdio.h>

float findArea(float a, float b, float h) {
    float area = ((a + b) / 2) * h;
    return area;
}

int main() {
    float a = 0, b = 0, h = 0;
    printf("Enter the length of the parallel side a: ");
    scanf("%f", &a);
    printf("Enter the length of the parallel side b: ");
    scanf("%f", &b);
    printf("Enter the height of the trapezium: ");
    scanf("%f", &h);

    float result = findArea(a, b, h);
    printf("The area of the trapezium is: %.2f\n", result);
    return 0;
}