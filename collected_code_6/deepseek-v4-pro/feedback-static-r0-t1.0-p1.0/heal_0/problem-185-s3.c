#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    double a;
    double b;
    double c;
} Parabola;

Point find_focus(const Parabola *p) {
    Point focus;
    double h = -p->b / (2.0 * p->a);
    double k = p->a * h * h + p->b * h + p->c;
    double p_val = 1.0 / (4.0 * p->a);
    
    focus.x = h;
    focus.y = k + p_val;
    
    return focus;
}

int main(void) {
    Parabola p;
    Point focus;
    
    if (scanf("%lf %lf %lf", &p.a, &p.b, &p.c) != 3) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (fabs(p.a) < 1e-10) {
        fprintf(stderr, "Error: Coefficient 'a' cannot be zero\n");
        return EXIT_FAILURE;
    }
    
    focus = find_focus(&p);
    printf("Focus: (%.6f, %.6f)\n", focus.x, focus.y);
    
    return EXIT_SUCCESS;
}