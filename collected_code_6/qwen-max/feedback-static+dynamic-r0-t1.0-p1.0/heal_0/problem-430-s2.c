#include <stdio.h>

double find_directrix(double a) {
    return -1.0 / (4 * a);
}

int main() {
    double a;
    printf("Enter the coefficient 'a' of the parabola y = ax^2: ");
    if (scanf("%lf", &a) != 1 || a == 0) {
        fprintf(stderr, "Invalid input. Please enter a non-zero numeric value.\n");
        return 1;
    }
    double directrix = find_directrix(a);
    printf("The directrix of the parabola is x = %f\n", directrix);
    return 0;
}