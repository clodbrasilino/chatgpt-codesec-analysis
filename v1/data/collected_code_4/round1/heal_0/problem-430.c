#include <stdio.h>
#include <stdlib.h>

double find_directrix(double a, double b, double h, double k) {
    if(a == 0) {
        printf("Error! 'a' cannot be zero in the equation of parabola.\n");
        exit(1);
    }
    double directrix = k - (1 / (4 * a));
    return directrix;
}

int main() {
    double a, b, h, k;
    printf("Enter the values of a, b, h, k for the parabola equation (which is in the form (y - k) = a * (x - h)^2 + b ):\n");
    if(scanf("%lf %lf %lf %lf", &a, &b, &h, &k) != 4) {
        printf("Invalid input!\n");
        return 1;
    }
    double directrix = find_directrix(a, b, h, k);
    printf("The directrix of the parabola is: %.2lf\n", directrix);
    return 0;
}