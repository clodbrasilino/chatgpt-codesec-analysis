#include <stdio.h>
#include <stdlib.h>

enum triangle_type {
    TRIANGLE_INVALID,
    TRIANGLE_EQUILATERAL,
    TRIANGLE_ISOSCELES,
    TRIANGLE_SCALENE
};

static enum triangle_type classify_triangle(double a, double b, double c)
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

static const char *triangle_type_name(enum triangle_type type)
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
        return "Invalid";
    }
}

int main(void)
{
    double a;
    double b;
    double c;
    enum triangle_type type;

    printf("Enter three sides of the triangle: ");

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    type = classify_triangle(a, b, c);

    if (type == TRIANGLE_INVALID) {
        printf("The given sides do not form a valid triangle.\n");
    } else {
        printf("Triangle type: %s\n", triangle_type_name(type));
    }

    return EXIT_SUCCESS;
}