#include <stdio.h>

float areaOfParallelogram(float base, float height) {
    return base * height;
}

int main() {
    float base, height, area;

    printf("Enter base of the parallelogram: ");
    scanf("%f", &base);

    printf("Enter height of the parallelogram: ");
    scanf("%f", &height);

    area = areaOfParallelogram(base, height);

    printf("Area of the parallelogram is: %.2f\n", area);

    return 0;
}