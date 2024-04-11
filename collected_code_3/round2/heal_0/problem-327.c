#include <stdio.h>

int isIsosceles(int a, int b, int c) {
    if (a == b || a == c || b == c) {
        return 1;
    }
    return 0;
}

int main() {
    int side1, side2, side3;

    printf("Enter the sides of the triangle: ");
    scanf("%d %d %d", &side1, &side2, &side3);

    if (isIsosceles(side1, side2, side3)) {
        printf("The triangle is isosceles.\n");
    } else {
        printf("The triangle is not isosceles.\n");
    }

    return 0;
}