#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

double cylinder_surface_area(double radius) {
    if (radius <= 0.0) {
        return 0.0;
    }
    return M_PI * radius * radius;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     */
    if (strlen(argv[0]) >= 1024 || strlen(argv[1]) >= 1024) {
        return EXIT_FAILURE;
    }

    char *endptr;
    double radius = strtod(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Invalid input: radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    double area = cylinder_surface_area(radius);
    printf("%.6f\n", area);

    return EXIT_SUCCESS;
}