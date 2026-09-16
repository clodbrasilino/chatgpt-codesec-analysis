#include <stdio.h>
#include <stdlib.h>

int is_equilateral(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }

    if (a == b && b == c) {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
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