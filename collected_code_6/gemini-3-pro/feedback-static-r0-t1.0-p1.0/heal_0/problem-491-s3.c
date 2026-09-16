#include <stdio.h>
#include <math.h>

double sumOfGeometricProgression(double a, double r, int n) {
    if (n <= 0) {
        return 0.0;
    }
    
    if (r == 1.0) {
        return a * n;
    }
    
    return a * (1.0 - pow(r, n)) / (1.0 - r);
}

int main(void) {
    double a;
    double r;
    int n;
    double sum;

    if (scanf("%lf %lf %d", &a, &r, &n) != 3) {
        return 1;
    }

    if (n < 0) {
        return 1;
    }

    sum = sumOfGeometricProgression(a, r, n);
    printf("%.6f\n", sum);

    return 0;
}