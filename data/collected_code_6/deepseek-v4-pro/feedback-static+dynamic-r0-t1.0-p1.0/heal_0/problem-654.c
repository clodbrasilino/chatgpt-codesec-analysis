#include <stdio.h>

float rectangle_perimeter(float length, float width) {
    return 2.0f * (length + width);
}

int main(void) {
    float length;
    float width;
    float perimeter;

    printf("Enter rectangle length: ");
    if (scanf("%f", &length) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter rectangle width: ");
    if (scanf("%f", &width) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (length <= 0.0f || width <= 0.0f) {
        printf("Dimensions must be positive\n");
        return 1;
    }

    perimeter = rectangle_perimeter(length, width);
    printf("Perimeter: %.2f\n", perimeter);

    return 0;
}