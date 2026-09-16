#include <stdio.h>
#include <stdlib.h>

double sum_of_geometric_progression(double a, double r, int n) {
    if (n <= 0 || r == 1) {
        return 0;
    }
    if (r == -1 && n % 2 == 0) {
        return 0;
    }
    if (r == -1 && n % 2 != 0) {
        return a;
    }
    return a * (1 - pow(r, n)) / (1 - r);
}

int main() {
    double a = 1.0;
    double r = 2.0;
    int n = 5;
    double result = sum_of_geometric_progression(a, r, n);
    printf("Sum of the geometric progression: %.2f\n", result);
    return 0;
}