#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef enum {
    PARABOLA_OK = 0,
    PARABOLA_ERROR_INVALID_COEFFICIENT = -1,
    PARABOLA_ERROR_INVALID_INPUT = -2
} ParabolaStatus;

ParabolaStatus find_focus_vertical(double a, double b, double c, Point *focus)
{
    if (focus == NULL) {
        return PARABOLA_ERROR_INVALID_INPUT;
    }
    
    if (fabs(a) < 1e-12) {
        return PARABOLA_ERROR_INVALID_COEFFICIENT;
    }
    
    double h = -b / (2.0 * a);
    double k = c - (b * b) / (4.0 * a);
    double p = 1.0 / (4.0 * a);
    
    focus->x = h;
    focus->y = k + p;
    
    return PARABOLA_OK;
}

ParabolaStatus find_focus_horizontal(double a, double b, double c, Point *focus)
{
    if (focus == NULL) {
        return PARABOLA_ERROR_INVALID_INPUT;
    }
    
    if (fabs(a) < 1e-12) {
        return PARABOLA_ERROR_INVALID_COEFFICIENT;
    }
    
    double k = -b / (2.0 * a);
    double h = c - (b * b) / (4.0 * a);
    double p = 1.0 / (4.0 * a);
    
    focus->x = h + p;
    focus->y = k;
    
    return PARABOLA_OK;
}

int main(void)
{
    Point focus = {0.0, 0.0};
    ParabolaStatus status;
    double a, b, c;
    int orientation;
    
    printf("Enter parabola orientation (0 for vertical y=ax^2+bx+c, 1 for horizontal x=ay^2+by+c): ");
    if (scanf("%d", &orientation) != 1) {
        fprintf(stderr, "Error: Invalid input for orientation\n");
        return 1;
    }
    
    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: Invalid input for coefficients\n");
        return 1;
    }
    
    if (orientation == 0) {
        status = find_focus_vertical(a, b, c, &focus);
    } else if (orientation == 1) {
        status = find_focus_horizontal(a, b, c, &focus);
    } else {
        fprintf(stderr, "Error: Invalid orientation value\n");
        return 1;
    }
    
    if (status == PARABOLA_ERROR_INVALID_COEFFICIENT) {
        fprintf(stderr, "Error: Coefficient 'a' cannot be zero (not a parabola)\n");
        return 1;
    } else if (status != PARABOLA_OK) {
        fprintf(stderr, "Error: Failed to calculate focus\n");
        return 1;
    }
    
    printf("Focus: (%.6f, %.6f)\n", focus.x, focus.y);
    
    return 0;
}