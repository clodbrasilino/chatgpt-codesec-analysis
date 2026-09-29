#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TRIANGLE_INVALID,
    TRIANGLE_EQUILATERAL,
    TRIANGLE_ISOSCELES,
    TRIANGLE_SCALENE
} TriangleType;

static TriangleType find_triangle_type(unsigned long long a,
                                       unsigned long long b,
                                       unsigned long long c)
{
    unsigned long long temp;

    if (a == 0 || b == 0 || c == 0) {
        return TRIANGLE_INVALID;
    }

    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }

    if (b > c) {
        temp = b;
        b = c;
        c = temp;
    }

    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }

    if (a <= c - b) {
        return TRIANGLE_INVALID;
    }

    if (a == c) {
        return TRIANGLE_EQUILATERAL;
    }

    if (a == b || b == c) {
        return TRIANGLE_ISOSCELES;
    }

    return TRIANGLE_SCALENE;
}

static int parse_side(const char *text, unsigned long long *side)
{
    char *end;
    unsigned long long value;

    if (text == NULL || side == NULL || text[0] == '\0' || text[0] == '-') {
        return 0;
    }

    errno = 0;
    value = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || value == 0) {
        return 0;
    }

    *side = value;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned long long a;
    unsigned long long b;
    unsigned long long c;
    TriangleType type;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <side1> <side2> <side3>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_side(argv[1], &a) ||
        !parse_side(argv[2], &b) ||
        !parse_side(argv[3], &c)) {
        fprintf(stderr, "All sides must be positive integers.\n");
        return EXIT_FAILURE;
    }

    type = find_triangle_type(a, b, c);

    switch (type) {
        case TRIANGLE_EQUILATERAL:
            puts("Equilateral");
            return EXIT_SUCCESS;

        case TRIANGLE_ISOSCELES:
            puts("Isosceles");
            return EXIT_SUCCESS;

        case TRIANGLE_SCALENE:
            puts("Scalene");
            return EXIT_SUCCESS;

        case TRIANGLE_INVALID:
        default:
            puts("Invalid triangle");
            return EXIT_FAILURE;
    }
}