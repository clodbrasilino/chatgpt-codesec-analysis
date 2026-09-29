#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Vertex;

int find_parabola_vertex(double a, double b, double c, Vertex *result) {
    if (result == NULL) {
        return -1;
    }

    if (a == 0.0) {
        return -2;
    }

    result->x = -b / (2.0 * a);
    result->y = (4.0 * a * c - (b * b)) / (4.0 * a);

    return 0;
}

int main(int argc, char * const * argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return 1;
    }

    char *endptr_a, *endptr_b, *endptr_c;

    double a = strtod(argv[1], &endptr_a);
    double b = strtod(argv[2], &endptr_b);
    double c = strtod(argv[3], &endptr_c);

    if (*endptr_a != '\0' || *endptr_b != '\0' || *endptr_c != '\0') {
        fprintf(stderr, "Invalid input: arguments must be numeric\n");
        return 1;
    }

    Vertex v;
    int rc = find_parabola_vertex(a, b, c, &v);

    if (rc == -1) {
        fprintf(stderr, "Error: Null pointer passed to function\n");
        return 1;
    } else if (rc == -2) {
        fprintf(stderr, "Error: Coefficient 'a' cannot be zero for a parabola\n");
        return 1;
    }

    printf("Vertex: (%f, %f)\n", v.x, v.y);

    return 0;
}