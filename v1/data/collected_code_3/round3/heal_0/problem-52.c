#include <stdio.h>

float calculateArea(float base, float height) {
    return base * height;
}

int main() {
    float base, height, area;

    printf("Enter base: ");
    scanf("%f", &base);

    printf("Enter height: ");
    scanf("%f", &height);

    area = calculateArea(base, height);

    printf("Area of Parallelogram: %.2f\n", area);

    return 0;
}