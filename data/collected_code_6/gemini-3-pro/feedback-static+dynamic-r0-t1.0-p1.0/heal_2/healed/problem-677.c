#include <stdio.h>
#include <stdlib.h>

int is_valid_triangle(double a, double b, double c) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    if (argc == 4) {
        a = atof(argv[1]);
        b = atof(argv[2]);
        c = atof(argv[3]);
    } else {
        if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
            return 1;
        }
    }

    if (is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}