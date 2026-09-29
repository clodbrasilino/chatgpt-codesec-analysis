#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double sphere_surface_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 4.0 * PI * radius * radius;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    double radius;
    /* Possible weaknesses found:
     *  The scope of the variable 'input_buffer' can be reduced. [variableScope]
     */
    char input_buffer[256];
    char *endptr;

    if (argc > 1) {
        radius = strtod(argv[1], &endptr);
        if (*endptr != '\0') {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        printf("Enter radius: ");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            return EXIT_FAILURE;
        }
        radius = strtod(input_buffer, &endptr);
        if (*endptr != '\0' && *endptr != '\n') {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }

    if (radius < 0.0) {
        fprintf(stderr, "Radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    double area = sphere_surface_area(radius);
    printf("Surface area: %.10f\n", area);

    return EXIT_SUCCESS;
}