#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
    INVALID,
    EQUILATERAL,
    ISOSCELES,
    SCALENE
} TriangleType;

TriangleType find_triangle_type(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return INVALID;
    }

    if ((long)a + (long)b <= c || (long)a + (long)c <= b || (long)b + (long)c <= a) {
        return INVALID;
    }

    if (a == b && b == c) {
        return EQUILATERAL;
    }

    if (a == b || b == c || a == c) {
        return ISOSCELES;
    }

    return SCALENE;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <side1> <side2> <side3>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2, *endptr3;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    long val3 = strtol(argv[3], &endptr3, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0' || *endptr3 != '\0') {
        fprintf(stderr, "Invalid input: non-integer detected.\n");
        return EXIT_FAILURE;
    }

    if (val1 <= 0 || val2 <= 0 || val3 <= 0 || val1 > INT_MAX || val2 > INT_MAX || val3 > INT_MAX) {
        fprintf(stderr, "Invalid input: sides must be positive integers within int range.\n");
        return EXIT_FAILURE;
    }

    int a = (int)val1;
    int b = (int)val2;
    int c = (int)val3;

    TriangleType type = find_triangle_type(a, b, c);

    switch (type) {
        case INVALID:
            printf("Not a valid triangle\n");
            break;
        case EQUILATERAL:
            printf("Equilateral\n");
            break;
        case ISOSCELES:
            printf("Isosceles\n");
            break;
        case SCALENE:
            printf("Scalene\n");
            break;
    }

    return EXIT_SUCCESS;
}