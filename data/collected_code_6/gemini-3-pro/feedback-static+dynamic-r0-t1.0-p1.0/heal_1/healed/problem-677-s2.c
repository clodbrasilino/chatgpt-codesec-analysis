#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(double a, double b, double c) {
    if (a > 0 && b > 0 && c > 0 && (a + b > c) && (a + c > b) && (b + c > a)) {
        return true;
    }
    return false;
}

int main(void) {
    double a, b, c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (a <= 0 || b <= 0 || c <= 0) {
        fprintf(stderr, "Sides must be positive.\n");
        return 1;
    }

    if (is_valid_triangle(a, b, c)) {
        printf("Valid triangle.\n");
    } else {
        printf("Invalid triangle.\n");
    }

    return 0;
}