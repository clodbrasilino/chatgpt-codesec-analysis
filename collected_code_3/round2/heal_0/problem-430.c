#include <stdio.h>

double findDirectrix(double a, double h, double k) {
    return k - (1 / (4 * a));
}

int main() {
    double a, h, k;
    printf("Enter the values for a, h and k: ");
    scanf("%lf %lf %lf", &a, &h, &k);
    double directrix = findDirectrix(a, h, k);
    printf("The directrix of the parabola is: %lf\n", directrix);
    return 0;
}