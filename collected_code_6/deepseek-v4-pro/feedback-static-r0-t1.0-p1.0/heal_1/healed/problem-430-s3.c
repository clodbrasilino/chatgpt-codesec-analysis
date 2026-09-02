#include <stdio.h>
#include <math.h>

typedef struct {
    double a;
    double b;
    double c;
} Parabola;

double calculate_directrix(Parabola p) {
    if (fabs(p.a) < 1e-12) {
        return NAN;
    }
    
    double h = -p.b / (2.0 * p.a);
    double k = p.a * h * h + p.b * h + p.c;
    double p_value = 1.0 / (4.0 * p.a);
    
    return k - p_value;
}

int main(void) {
    Parabola par;
    
    printf("Enter coefficients a, b, c (y = ax^2 + bx + c): ");
    if (scanf("%lf %lf %lf", &par.a, &par.b, &par.c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (fabs(par.a) < 1e-12) {
        fprintf(stderr, "Not a parabola\n");
        return 1;
    }
    
    double directrix_y = calculate_directrix(par);
    
    if (isnan(directrix_y)) {
        fprintf(stderr, "Error calculating directrix\n");
        return 1;
    }
    
    printf("Directrix: y = %.6f\n", directrix_y);
    
    return 0;
}