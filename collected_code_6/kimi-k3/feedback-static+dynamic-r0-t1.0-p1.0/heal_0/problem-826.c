#include <stdio.h>
#include <stdbool.h>

typedef enum {
    NOT_A_TRIANGLE,
    EQUILATERAL,
    ISOSCELES,
    SCALENE
} TriangleType;

static bool is_valid_triangle(double a, double b, double c) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }
    if (a + b <= c || b + c <= a || a + c <= b) {
        return false;
    }
    return true;
}

TriangleType get_triangle_type(double a, double b, double c) {
    if (!is_valid_triangle(a, b, c)) {
        return NOT_A_TRIANGLE;
    }
    if (a == b && b == c) {
        return EQUILATERAL;
    }
    if (a == b || b == c || a == c) {
        return ISOSCELES;
    }
    return SCALENE;
}

int main(void) {
    double a, b, c;
    
    printf("Enter three sides of triangle: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    TriangleType type = get_triangle_type(a, b, c);
    
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
        case NOT_A_TRIANGLE:
        default:
            printf("Not a valid triangle\n");
            break;
    }
    
    return 0;
}