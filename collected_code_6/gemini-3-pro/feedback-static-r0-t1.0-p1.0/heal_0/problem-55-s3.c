#include <stdio.h>
#include <math.h>

double find_geometric_term(double a, double r, int n) {
    if (n < 1) {
        return 0.0;
    }
    return a * pow(r, (double)(n - 1));
}

int main(void) {
    double a = 0.0;
    double r = 0.0;
    int n = 0;

    if (scanf("%lf %lf %d", &a, &r, &n) != 3) {
        return 1;
    }

    if (n < 1) {
        return 1;
    }

    double term = find_geometric_term(a, r, n);
    printf("%.6f\n", term);

    return 0;
}