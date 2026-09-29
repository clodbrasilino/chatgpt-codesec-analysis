#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

Point find_parabola_focus(double a, double b, double c, int *err) {
    Point focus;
    if (a == 0.0) {
        focus.x = 0.0;
        focus.y = 0.0;
        *err = 1;
        return focus;
    }
    focus.x = -b / (2.0 * a);
    focus.y = (1.0 - (b * b) + (4.0 * a * c)) / (4.0 * a);
    *err = 0;
    return focus;
}

int main(int argc, char * const argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    char *endptr_a, *endptr_b, *endptr_c;
    double a = strtod(argv[1], &endptr_a);
    double b = strtod(argv[2], &endptr_b);
    double c = strtod(argv[3], &endptr_c);
    if (*endptr_a != '\0' || *endptr_b != '\0' || *endptr_c != '\0') {
        return EXIT_FAILURE;
    }
    int err;
    Point focus = find_parabola_focus(a, b, c, &err);
    if (err != 0) {
        return EXIT_FAILURE;
    }
    printf("(%f, %f)\n", focus.x, focus.y);
    return EXIT_SUCCESS;
}