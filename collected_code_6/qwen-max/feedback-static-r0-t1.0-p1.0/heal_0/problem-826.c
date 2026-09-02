#include <stdio.h>

char* findTriangleType(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) return "Invalid";
    if (a + b <= c || a + c <= b || b + c <= a) return "Not a triangle";

    if (a == b && b == c) return "Equilateral";
    if (a == b || a == c || b == c) return "Isosceles";
    return "Scalene";
}

int main() {
    int a, b, c;
    printf("Enter three sides of the triangle: ");
    scanf("%d %d %d", &a, &b, &c);

    char* type = findTriangleType(a, b, c);
    printf("The triangle is %s\n", type);
    return 0;
}