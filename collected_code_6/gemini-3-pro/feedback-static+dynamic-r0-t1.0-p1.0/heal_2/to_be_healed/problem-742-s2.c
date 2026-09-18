#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calculate_tetrahedron_area(double edge, double *area) {
    if (edge < 0.0 || area == NULL) {
        return -1;
    }
    
    *area = sqrt(3.0) * edge * edge;
    
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <edge_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr = NULL;
    double edge = strtod(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid numerical input.\n");
        return EXIT_FAILURE;
    }

    double area = 0.0;
    if (calculate_tetrahedron_area(edge, &area) != 0) {
        fprintf(stderr, "Error: Edge length cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", area);

    return EXIT_SUCCESS;
}