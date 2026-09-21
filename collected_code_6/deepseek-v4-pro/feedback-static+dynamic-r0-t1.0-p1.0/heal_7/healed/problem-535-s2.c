#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <float.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define INPUT_BUFFER_SIZE 256

double cylinder_circle_area(double radius) {
    if (radius < 0) {
        return -1.0;
    }
    return M_PI * radius * radius;
}

int main(void) {
    double radius;
    char input[INPUT_BUFFER_SIZE + 1];
    char *endptr;
    size_t len;
    int c;
    int ch;

    printf("Enter the radius of the cylinder: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';
    len = strnlen(input, sizeof(input));
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        if (len == sizeof(input) - 1) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            fprintf(stderr, "Input too long. Maximum %zu characters allowed.\n", (size_t)(INPUT_BUFFER_SIZE - 1));
            return EXIT_FAILURE;
        }
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &endptr);

    if (endptr == input) {
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Input value out of range.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0) {
        fprintf(stderr, "Radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    if (radius > sqrt(DBL_MAX / M_PI)) {
        fprintf(stderr, "Radius too large, calculation would overflow.\n");
        return EXIT_FAILURE;
    }

    double area = cylinder_circle_area(radius);
    printf("The area of the top/bottom surface is: %.6f\n", area);

    return EXIT_SUCCESS;
}