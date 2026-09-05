#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Vertex;

int find_parabola_vertex(double a, double b, double c, Vertex *result) {
    if (a == 0.0) {
        return -1;
    }
    if (result == NULL) {
        return -1;
    }
    result->x = -b / (2.0 * a);
    result->y = c - (b * b) / (4.0 * a);
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
    double a = strtod(argv[1], &endptr);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    double b = strtod(argv[2], &endptr);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    double c = strtod(argv[3], &endptr);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    Vertex v;
    if (find_parabola_vertex(a, b, c, &v) != 0) {
        fprintf(stderr, "Invalid input: a cannot be 0\n");
        return EXIT_FAILURE;
    }

    printf("Vertex: (%f, %f)\n", v.x, v.y);
    return EXIT_SUCCESS;
}