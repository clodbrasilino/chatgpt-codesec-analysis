#include <stdio.h>

enum TriangleType {
    EQUILATERAL,
    ISOSCELES,
    SCALENE,
    INVALID
};

enum TriangleType triangleType(int a, int b, int c) {
    if (a == b && b == c)
        return EQUILATERAL;
    else if (a == b || b == c || c == a)
        return ISOSCELES;
    else if (a + b <= c || a + c <= b || b + c <= a)
        return INVALID;
    else
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
            printf("The triangle is invalid.\n");
    }

    return 0;
}