#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_valid_triangle(double a, double b, double c) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return false;
    }
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return true;
    }
    return false;
}

int main(int argc, const char *argv[]) {
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    if (argc == 4) {
        a = atof(argv[1]);
        b = atof(argv[2]);
        c = atof(argv[3]);
    } else {
        if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
            a = 0.0;
            b = 0.0;
            c = 0.0;
        }
    }

    if (is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}