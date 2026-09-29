#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int find_parabola_focus(double a, double b, double c, double *fx, double *fy) {
    if (a == 0.0) {
        return -1;
    }
    if (fx == NULL || fy == NULL) {
        return -2;
    }
    *fx = -b / (2.0 * a);
    *fy = c - (b * b) / (4.0 * a);
    return 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr_a, *endptr_b, *endptr_c;
    double a = strtod(argv[1], &endptr_a);
    double b = strtod(argv[2], &endptr_b);
    double c = strtod(argv[3], &endptr_c);
    if (*endptr_a != '\0' || *endptr_b != '\0' || *endptr_c != '\0') {
        fprintf(stderr, "Invalid numeric input\n");
        return EXIT_FAILURE;
    }
    double fx, fy;
    int ret = find_parabola_focus(a, b, c, &fx, &fy);
    if (ret != 0) {
        if (ret == -1) {
            fprintf(stderr, "Coefficient 'a' cannot be zero for a parabola\n");
        } else {
            fprintf(stderr, "Null pointer provided for output coordinates\n");
        }
        return EXIT_FAILURE;
    }
    printf("Focus: (%.6f, %.6f)\n", fx, fy);
    return EXIT_SUCCESS;
}