#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SCALENE,
    ISOSCELES,
    EQUILATERAL,
    INVALID
} TriangleType;

TriangleType checkTriangleType(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return INVALID;
    }
    if ((a + b <= c) || (a + c <= b) || (b + c <= a)) {
        return INVALID;
    }

    if (a == b && b == c) {
        return EQUILATERAL;
    } else if (a == b || b == c || a == c) {
        return ISOSCELES;
    } else {
        return SCALENE;
    }
}

int main(void) {
    double a, b, c;
    TriangleType type;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: Invalid input format.\n");
        return EXIT_FAILURE;
    }

    type = checkTriangleType(a, b, c);

    switch (type) {
        case EQUILATERAL:
            printf("Equilateral\n");
            break;
        case ISOSCELES:
            printf("Isosceles\n");
            break;
        case SCALENE:
            printf("Scalene\n");
            break;
        case INVALID:
            printf("Invalid\n");
            break;
        default:
            fprintf(stderr, "Error: Unknown triangle type.\n");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}