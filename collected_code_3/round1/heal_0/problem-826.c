#include <stdio.h>

enum TriangleType {
    EQUILATERAL,
    ISOSCELES,
    SCALENE,
    INVALID
};

enum TriangleType triangleType(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return INVALID;
    }
    if (a == b && b == c) {
        return EQUILATERAL;
    }
    if (a == b || b == c || c == a) {
        return ISOSCELES;
    }
    return SCALENE;
}

int main() {
    int a, b, c;
    printf("Enter the sides of the triangle: ");
    scanf("%d %d %d", &a, &b, &c);

    switch (triangleType(a, b, c)) {
        case EQUILATERAL:
            printf("The triangle is equilateral.\n");
            break;
        case ISOSCELES:
            printf("The triangle is isosceles.\n");
            break;
        case SCALENE:
            printf("The triangle is scalene.\n");
            break;
        default:
            printf("Invalid triangle.\n");
    }

    return 0;
}