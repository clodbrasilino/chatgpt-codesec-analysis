#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

double calculate_pentagon_area(double side_length) {
    if (side_length <= 0) {
        return -1.0;
    }
    return (5.0 * side_length * side_length) / (4.0 * tan(M_PI / 5.0));
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    double side_length = strtod(argv[1], &endptr);

    if (errno == ERANGE || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid input. Please provide a valid numeric value.\n");
        return EXIT_FAILURE;
    }

    double area = calculate_pentagon_area(side_length);

    if (area < 0) {
        fprintf(stderr, "Error: Side length must be greater than zero.\n");
        return EXIT_FAILURE;
    }

    printf("Area of pentagon: %.6f\n", area);

    return EXIT_SUCCESS;
}