#include <stdio.h>
#include <stdlib.h>

int is_equilateral(double a, double b, double c) {
    int valid_a = (a > 0);
    int valid_b = (b > 0);
    int valid_c = (c > 0);

    if (!valid_a || !valid_b || !valid_c) {
        return 0;
    }

    if (a == b && b == c) {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    double a, b, c;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <side_a> <side_b> <side_c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    a = atof(argv[1]);
    b = atof(argv[2]);
    c = atof(argv[3]);

    if (is_equilateral(a, b, c)) {
        printf("Equilateral\n");
    } else {
        printf("Not Equilateral\n");
    }

    return EXIT_SUCCESS;
}