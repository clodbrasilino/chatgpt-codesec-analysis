#include <stdio.h>
#include <stdlib.h>

double trapezium_area(double base1, double base2, double height) {
    if (base1 < 0 || base2 < 0 || height < 0) {
        return -1.0;
    }
    return 0.5 * (base1 + base2) * height;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    char *endptr1;
    char *endptr2;
    char *endptr3;

    double base1 = strtod(argv[1], &endptr1);
    double base2 = strtod(argv[2], &endptr2);
    double height = strtod(argv[3], &endptr3);

    if (endptr1 == argv[1] || endptr2 == argv[2] || endptr3 == argv[3]) {
        return 1;
    }

    double result = trapezium_area(base1, base2, height);

    if (result < 0) {
        return 1;
    }

    printf("%.6f\n", result);

    return 0;
}