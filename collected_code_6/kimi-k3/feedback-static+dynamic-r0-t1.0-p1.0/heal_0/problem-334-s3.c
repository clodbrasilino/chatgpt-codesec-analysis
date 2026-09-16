#include <stdio.h>

int isValidTriangle(float a, float b, float c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if ((a + b > c) && (b + c > a) && (a + c > b)) {
        return 1;
    }
    return 0;
}

int main(void) {
    float a, b, c;

    printf("Enter three sides of the triangle: ");
    if (scanf("%f %f %f", &a, &b, &c) != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    if (isValidTriangle(a, b, c)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }

    return 0;
}