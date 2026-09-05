#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    double diff = *(const double *)a - *(const double *)b;
    if (diff > 0.0) return 1;
    if (diff < 0.0) return -1;
    return 0;
}

const char* find_triangle_type(double side1, double side2, double side3) {
    if (side1 <= 0.0 || side2 <= 0.0 || side3 <= 0.0) {
        return "NotATriangle";
    }

    double sides[3] = {side1, side2, side3};
    qsort(sides, 3, sizeof(double), compare);

    if (sides[0] + sides[1] <= sides[2] + 1e-9) {
        return "NotATriangle";
    }

    if (sides[0] == sides[1] && sides[1] == sides[2]) {
        return "Equilateral";
    }

    if (sides[0] == sides[1] || sides[1] == sides[2]) {
        return "Isosceles";
    }

    return "Scalene";
}

int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <side1> <side2> <side3>\n", argv[0]);
        return 1;
    }

    char *endptr1, *endptr2, *endptr3;
    double side1 = strtod(argv[1], &endptr1);
    double side2 = strtod(argv[2], &endptr2);
    double side3 = strtod(argv[3], &endptr3);

    if (endptr1 == argv[1] || *endptr1 != '\0' ||
        endptr2 == argv[2] || *endptr2 != '\0' ||
        endptr3 == argv[3] || *endptr3 != '\0') {
        fprintf(stderr, "Invalid input: All arguments must be valid numeric values.\n");
        return 1;
    }

    const char *type = find_triangle_type(side1, side2, side3);
    printf("%s\n", type);

    return 0;
}