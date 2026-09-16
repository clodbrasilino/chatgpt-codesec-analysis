#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

int find_parabola_directrix(double a, double b, double c, double *directrix) {
    if (directrix == NULL) {
        return -1;
    }

    if (a == 0.0) {
        return -2;
    }

    *directrix = c - (b * b / (4.0 * a));
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    double a = strtod(argv[1], &endptr);
    if (errno != 0 || *endptr != '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    double b = strtod(argv[2], &endptr);
    if (errno != 0 || *endptr != '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    double c = strtod(argv[3], &endptr);
    if (errno != 0 || *endptr != '\0') {
        return EXIT_FAILURE;
    }

    double directrix;
    int status = find_parabola_directrix(a, b, c, &directrix);

    if (status == -1) {
        fprintf(stderr, "Error: Null pointer passed to function.\n");
        return EXIT_FAILURE;
    }

    if (status == -2) {
        fprintf(stderr, "Error: Coefficient 'a' cannot be zero for a parabola.\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", directrix);
    return EXIT_SUCCESS;
}