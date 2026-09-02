#include <stdio.h>

char *determine_triangle_type(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) return "Invalid";
    if (a + b <= c || a + c <= b || b + c <= a) return "Invalid";

    if (a == b && b == c) return "Equilateral";
    if (a == b || a == c || b == c) return "Isosceles";
    return "Scalene";
}

int main() {
    int side1, side2, side3;
    char *result;

    printf("Enter the sides of the triangle: ");
    scanf("%d %d %d", &side1, &side2, &side3);

    result = determine_triangle_type(side1, side2, side3);
    printf("The triangle is: %s\n", result);

    return 0;
}