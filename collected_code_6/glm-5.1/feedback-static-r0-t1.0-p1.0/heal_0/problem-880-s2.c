#include <stdio.h>
#include <math.h>

int find_num_solutions(double a, double b, double c) {
    if (a == 0.0 && b == 0.0) {
        if (c == 0.0) {
            return -1;
        }
        return 0;
    }
    if (a == 0.0) {
        return 1;
    }
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant > 0.0) {
        return 2;
    }
    if (discriminant == 0.0) {
        return 1;
    }
    return 0;
}

int main(void) {
    double a, b, c;
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }
    int solutions = find_num_solutions(a, b, c);
    printf("%d\n", solutions);
    return 0;
}