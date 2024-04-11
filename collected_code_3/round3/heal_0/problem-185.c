#include <stdio.h>
#include <math.h>

struct Point {
    double x;
    double y;
};

struct Parabola {
    double a;
    double b;
    double c;
};

struct Point findFocus(struct Parabola p) {
    struct Point focus;
    focus.x = -p.b / (2 * p.a);
    focus.y = (1 - (p.b * p.b - 4 * p.a * p.c)) / (4 * p.a);
    return focus;
}

int main() {
    struct Parabola p;
    p.a = 1;
    p.b = 0;
    p.c = 0;

    struct Point focus = findFocus(p);

    printf("Focus of the parabola is at (%f, %f)\n", focus.x, focus.y);

    return 0;
}