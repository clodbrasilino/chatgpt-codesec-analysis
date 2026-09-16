#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedron_surface_area(double edge, double *area)
{
    if (area == NULL || !isfinite(edge) || edge < 0.0) {
        return 0;
    }

    *area = sqrt(3.0) * edge * edge;
    return isfinite(*area);
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    double edge;
    double area;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <edge_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    edge = strtod(argv[1], &end);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        !isfinite(edge) || edge < 0.0) {
        fprintf(stderr, "Invalid edge length\n");
        return EXIT_FAILURE;
    }

    if (!tetrahedron_surface_area(edge, &area)) {
        fprintf(stderr, "Unable to calculate a finite surface area\n");
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}