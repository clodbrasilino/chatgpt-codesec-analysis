#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

void find_focus(double a, double b, double c, Point* focus) {
    if (focus == NULL) {
        return;
    }
    
    if (fabs(a) < 1e-9) {
        focus->x = 0.0;
        focus->y = 0.0;
        return;
    }

    focus->x = -b / (2.0 * a);
    focus->y = (4.0 * a * c - b * b + 1.0) / (4.0 * a);
}

int main(void) {
    double a, b, c;
    Point focus;
    
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return EXIT_FAILURE;
    }
    
    if (fabs(a) < 1e-9) {
        return EXIT_FAILURE;
    }

    find_focus(a, b, c, &focus);
    
    printf("%.6f %.6f\n", focus.x, focus.y);
    
    return EXIT_SUCCESS;
}