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

int main(int argc, const char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <edge_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr = NULL;
    double edge = strtod(argv[1], &endptr);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    if (endptr == (char *)argv[1] || *endptr != '\0') {
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