#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedron_surface_area(double edge, double *area)
{
    double result;

    if (area == NULL || !isfinite(edge) || edge <= 0.0) {
        return 0;
    }

    result = sqrt(3.0) * edge * edge;

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

int main(void)
{
    char input[256];
    char *end;
    double edge;
    double area;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the edge length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    edge = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid edge length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Unexpected characters in input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!tetrahedron_surface_area(edge, &area)) {
        fputs("Edge length must be a finite positive number within range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}