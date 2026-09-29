#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_valid_triangle(double a, double b, double c);

bool is_valid_triangle(double a, double b, double c) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return true;
    }
    return false;
}

int main(void) {
    double side_a = 0.0;
    double side_b = 0.0;
    double side_c = 0.0;

    if (scanf("%lf %lf %lf", &side_a, &side_b, &side_c) != 3) {
        fprintf(stderr, "Invalid input format.\n");
        return EXIT_FAILURE;
    }

    if (is_valid_triangle(side_a, side_b, side_c)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }

    return EXIT_SUCCESS;
}