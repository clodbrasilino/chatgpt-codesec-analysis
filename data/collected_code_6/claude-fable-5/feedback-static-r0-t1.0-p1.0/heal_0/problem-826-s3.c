#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TRIANGLE_INVALID,
    TRIANGLE_EQUILATERAL,
    TRIANGLE_ISOSCELES,
    TRIANGLE_SCALENE
} triangle_type_t;

static triangle_type_t classify_triangle(double a, double b, double c)
{
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return TRIANGLE_INVALID;
    }

    if ((a + b <= c) || (b + c <= a) || (a + c <= b)) {
        return TRIANGLE_INVALID;
    }

    if (a == b && b == c) {
        return TRIANGLE_EQUILATERAL;
    }

    if (a == b || b == c || a == c) {
        return TRIANGLE_ISOSCELES;
    }

    return TRIANGLE_SCALENE;
}

static const char *triangle_type_name(triangle_type_t type)
{
    switch (type) {
    case TRIANGLE_EQUILATERAL:
        return "Equilateral";
    case TRIANGLE_ISOSCELES:
        return "Isosceles";
    case TRIANGLE_SCALENE:
        return "Scalene";
    case TRIANGLE_INVALID:
    default:
        return "Invalid triangle";
    }
}

int main(void)
{
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    triangle_type_t type;

    printf("Enter three sides of the triangle: ");

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    type = classify_triangle(a, b, c);

    if (printf("Result: %s\n", triangle_type_name(type)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}