#include <stdio.h>

enum TriangleType {
    Equilateral,
    Isosceles,
    Scalene,
    Invalid
};

enum TriangleType triangleType(int a, int b, int c) {
    if (a == b && b == c)
        return Equilateral;
    else if (a == b || b == c || c == a)
        return Isosceles;
    else if (a + b <= c || a + c <= b || b + c <= a)
        return Invalid;
    else
        return Scalene;
}

int main() {
    int a, b, c;
    printf("Enter the sides of the triangle: ");
    scanf("%d %d %d", &a, &b, &c);

    switch (triangleType(a, b, c)) {
        case Equilateral:
            printf("The triangle is equilateral.\n");
            break;
        case Isosceles:
            printf("The triangle is isosceles.\n");
            break;
        case Scalene:
            printf("The triangle is scalene.\n");
            break;
        case Invalid:
            printf("The triangle is invalid.\n");
            break;
    }

    return 0;
}