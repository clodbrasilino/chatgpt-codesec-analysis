#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(double a, double b, double c) {
    return (a > 0 && b > 0 && c > 0 && (a + b > c) && (a + c > b) && (b + c > a));
}

int main(void) {
    double a, b, c;

    if (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
        if (is_valid_triangle(a, b, c)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }

    return 0;
}