#include <stdio.h>

enum TriangleType {
    EQUILATERAL,
    ISOSCELES,
    SCALENE,
    INVALID
};

enum TriangleType determine_triangle_type(double side1, double side2, double side3) {
    if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
        return INVALID;
    }

    if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) {
        return INVALID;
    }

    if (side1 == side2 && side2 == side3) {
        return EQUILATERAL;
    }

    if (side1 == side2 || side2 == side3 || side1 == side3) {
        return ISOSCELES;
    }

    return SCALENE;
}

void print_triangle_type(enum TriangleType type) {
    switch (type) {
        case EQUILATERAL:
            printf("Equilateral triangle\n");
            break;
        case ISOSCELES:
            printf("Isosceles triangle\n");
            break;
        case SCALENE:
            printf("Scalene triangle\n");
            break;
        case INVALID:
            printf("Invalid triangle\n");
            break;
    }
}

int main(void) {
    double a, b, c;
    enum TriangleType result;

    printf("Enter three sides of a triangle: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }

    result = determine_triangle_type(a, b, c);
    print_triangle_type(result);

    return 0;
}