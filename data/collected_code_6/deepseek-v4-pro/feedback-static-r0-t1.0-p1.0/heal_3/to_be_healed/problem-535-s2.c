#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double cylinder_circle_area(double radius) {
    if (radius < 0) {
        return -1.0;
    }
    return M_PI * radius * radius;
}

int main(void) {
    double radius;
    char *buffer = NULL;
    size_t bufsize = 0;
    size_t len;
    char *endptr;
    ssize_t bytes_read;

    printf("Enter the radius of the cylinder: ");

    bytes_read = getline(&buffer, &bufsize, stdin);

    if (bytes_read == -1) {
        free(buffer);
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'bytes_read==0' is not redundant
     */
    if (buffer == NULL || bytes_read == 0) {
        free(buffer);
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assignment 'len=(unsigned long)bytes_read', assigned value is greater than 0
     */
    len = (size_t)bytes_read;

    /* Possible weaknesses found:
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     *  Condition 'len>0' is always true
     */
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        free(buffer);
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(buffer, &endptr);

    if (endptr == buffer || *endptr != '\0') {
        free(buffer);
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        free(buffer);
        fprintf(stderr, "Value out of range.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0) {
        free(buffer);
        fprintf(stderr, "Radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    double area = cylinder_circle_area(radius);
    printf("The area of the top/bottom surface is: %.6f\n", area);

    free(buffer);
    return EXIT_SUCCESS;
}