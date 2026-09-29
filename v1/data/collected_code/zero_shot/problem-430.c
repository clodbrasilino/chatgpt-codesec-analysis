#include <stdio.h>

void findDirectrix(double a, double b, double c) {
    if (a == 0) {
        printf("The directrix is parallel to the y-axis.");
    } else {
        double p = (b * b - 4 * a * c) / (4 * a);
        printf("The directrix is y = %.2lf\n", -p);
    }
}

int main() {
    double a, b, c;
    printf("Enter the coefficients (a, b, c) of the parabola:\n");
    scanf("%lf %lf %lf", &a, &b, &c);
    findDirectrix(a, b, c);
    return 0;
}