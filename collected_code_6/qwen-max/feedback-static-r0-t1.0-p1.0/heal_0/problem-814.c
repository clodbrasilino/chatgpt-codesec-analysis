#include <stdio.h>
#include <math.h>

double calculate_area_rhombus(double d1, double d2) {
    return 0.5 * d1 * d2;
}

int main() {
    double diagonal1 = 0.0, diagonal2 = 0.0;

    if (scanf("%lf %lf", &diagonal1, &diagonal2) != 2) {
        return 1;
    }

    double area = calculate_area_rhombus(diagonal1, diagonal2);
    printf("%.2f\n", area);

    return 0;
}