#include <stdio.h>
#include <math.h>

typedef struct {
    double h;
    double k;
} Point;

typedef struct {
    double a;
    double b;
    double c;
    int is_vertical;
} Parabola;

int find_focus(const Parabola *parabola, Point *focus) {
    if (parabola == NULL || focus == NULL) {
        return -1;
    }
    
    if (parabola->is_vertical) {
        if (fabs(parabola->a) < 1e-12) {
            return -1;
        }
        focus->h = -parabola->b / (2.0 * parabola->a);
        focus->k = (4.0 * parabola->a * parabola->c - 
                   parabola->b * parabola->b + 1.0) / (4.0 * parabola->a);
    } else {
        if (fabs(parabola->a) < 1e-12) {
            return -1;
        }
        focus->h = (4.0 * parabola->a * parabola->c - 
                   parabola->b * parabola->b - 1.0) / (4.0 * parabola->a);
        focus->k = -parabola->b / (2.0 * parabola->a);
    }
    
    return 0;
}

int main(void) {
    Parabola parabola;
    Point focus;
    int result;
    char orientation;
    
    printf("Enter parabola orientation (v for vertical, h for horizontal): ");
    if (scanf(" %c", &orientation) != 1) {
        fprintf(stderr, "Error reading orientation\n");
        return 1;
    }
    
    if (orientation == 'v' || orientation == 'V') {
        parabola.is_vertical = 1;
        printf("Enter coefficients a, b, c for y = ax^2 + bx + c: ");
    } else if (orientation == 'h' || orientation == 'H') {
        parabola.is_vertical = 0;
        printf("Enter coefficients a, b, c for x = ay^2 + by + c: ");
    } else {
        fprintf(stderr, "Invalid orientation. Use 'v' or 'h'\n");
        return 1;
    }
    
    if (scanf("%lf %lf %lf", &parabola.a, &parabola.b, &parabola.c) != 3) {
        fprintf(stderr, "Error reading coefficients\n");
        return 1;
    }
    
    result = find_focus(&parabola, &focus);
    
    if (result == 0) {
        printf("Focus: (%.6f, %.6f)\n", focus.h, focus.k);
    } else {
        fprintf(stderr, "Error: Invalid parabola (coefficient 'a' cannot be zero)\n");
        return 1;
    }
    
    return 0;
}