#include <stdio.h>
#include <math.h>

typedef enum {
    TRIANGLE_INVALID,
    TRIANGLE_EQUILATERAL,
    TRIANGLE_ISOSCELES,
    TRIANGLE_SCALENE
} TriangleType;

static int is_valid_triangle(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return 0;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }
    return 1;
}

static int are_equal(double x, double y) {
    return fabs(x - y) < 1e-10;
}

TriangleType get_triangle_type(double a, double b, double c) {
    if (!is_valid_triangle(a, b, c)) {
        return TRIANGLE_INVALID;
    }
    
    if (are_equal(a, b) && are_equal(b, c)) {
        return TRIANGLE_EQUILATERAL;
    }
    
    if (are_equal(a, b) || are_equal(b, c) || are_equal(a, c)) {
        return TRIANGLE_ISOSCELES;
    }
    
    return TRIANGLE_SCALENE;
}

const char* triangle_type_to_string(TriangleType type) {
    switch (type) {
        case TRIANGLE_EQUILATERAL:
            return "Equilateral";
        case TRIANGLE_ISOSCELES:
            return "Isosceles";
        case TRIANGLE_SCALENE:
            return "Scalene";
        case TRIANGLE_INVALID:
        default:
            return "Invalid";
    }
}

int main(void) {
    double sides[3];
    int result;
    
    printf("Enter three sides of a triangle: ");
    result = scanf("%lf %lf %lf", &sides[0], &sides[1], &sides[2]);
    
    if (result != 3) {
        printf("Error: Please enter three valid numbers.\n");
        return 1;
    }
    
    TriangleType type = get_triangle_type(sides[0], sides[1], sides[2]);
    printf("Triangle type: %s\n", triangle_type_to_string(type));
    
    return 0;
}