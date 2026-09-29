#include <stdio.h>

double findDirectrix(double a, double h, double k) {
    return k - (1/(4*a));
}

int main() {
    double a = 5.0, h = 3.0, k = 2.0;
    double directrix = findDirectrix(a, h, k);
    printf("Directrix of the parabola is: %f\n", directrix);
    return 0;
}