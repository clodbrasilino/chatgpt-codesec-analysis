#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    double a;
    double b;
    double c;
} Parabola;

Point find_focus(Parabola p) {
    Point focus;
    if (p.a == 0.0) {
        fprintf(stderr, "Error: 'a' cannot be zero for a parabola.\n");
        exit(EXIT_FAILURE);
    }
    focus.x = -p.b / (2 * p.a);
    focus.y = (4 * p.a * p.c - p.b * p.b + 1) / (4 * p.a);
    return focus;
}

int main(void) {
    Parabola p;
    Point focus;
    int result;

    printf("Enter coefficients a, b, c for parabola y = ax^2 + bx + c: ");
    result = scanf("%lf %lf %lf", &p.a, &p.b, &p.c);

    if (result != 3) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (p.a == 0.0) {
        fprintf(stderr, "Error: Not a parabola (a = 0).\n");
        return EXIT_FAILURE;
    }

    focus = find_focus(p);

    printf("The focus of the parabola is at (%.2f, %.2f)\n", focus.x, focus.y);

    return EXIT_SUCCESS;
}