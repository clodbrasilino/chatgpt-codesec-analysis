#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(double a, double b, double c) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }
    return (a + b > c) && (a + c > b) && (b + c > a);
}

int main(void) {
    double side_a = 0.0;
    double side_b = 0.0;
    double side_c = 0.0;

    if (scanf("%lf %lf %lf", &side_a, &side_b, &side_c) == 3) {
        if (is_valid_triangle(side_a, side_b, side_c)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    } else {
        printf("False\n");
    }

    return 0;
}