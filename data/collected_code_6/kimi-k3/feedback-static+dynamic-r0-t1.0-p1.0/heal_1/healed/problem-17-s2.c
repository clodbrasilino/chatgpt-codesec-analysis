#include <stdio.h>

double square_perimeter(double side);

int main(void) {
    double side;
    if (scanf("%lf", &side) != 1 || side < 0) {
        return 1;
    }
    printf("%.0f\n", square_perimeter(side));
    return 0;
}

double square_perimeter(double side) {
    return 4.0 * side;
}